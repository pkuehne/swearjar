#include "window.h"
#include "screen.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Window::Window(Screen& s, unsigned int x, unsigned int y, unsigned int width,
               unsigned int height)
    : m_screen(s), m_x(x), m_y(y), m_width(width), m_height(height) {
    initialize();
}

Window::Window(Screen& screen) : m_screen(screen) {
    int screenHeight = 0, screenWidth = 0;
    screen.curses().get_screen_size(screenHeight, screenWidth);
    m_height = static_cast<unsigned int>(screenHeight);
    m_width = static_cast<unsigned int>(screenWidth);

    initialize();
}

Window::Window(Screen& screen, unsigned int width, unsigned int height)
    : Window(screen, 0, 0, 0, 0) {
    int screenHeight = 0, screenWidth = 0;
    screen.curses().get_screen_size(screenHeight, screenWidth);

    m_height = height;
    m_width = width;

    m_x = (screenWidth / 2) - (width / 2);
    m_y = (screenHeight / 2) - (height / 2);

    initialize();
}

void Window::initialize() {
    m_id = screen().curses().newwin(m_height, m_width, m_y, m_x);
    m_baseWidget = std::make_unique<BaseWidget>();
    m_baseWidget->width(m_width);
    m_baseWidget->height(m_height);

    m_render = std::make_unique<RenderContext>(screen().curses(), m_id);
    m_render->width(m_width);
    m_render->height(m_height);
}

Window::~Window() {
}

void Window::setWindowStyleFullScreen() {
    m_style = WindowStyle::FullScreen;
}

void Window::setWindowStyleFractional(unsigned int widthFraction,
                                      unsigned int heightFraction) {
    m_style = WindowStyle::Fractional;
    m_params.fractionalWidth = widthFraction;
    m_params.fractionalHeight = heightFraction;
}

void Window::setWindowStyleFixed(unsigned int x, unsigned int y,
                                 unsigned int width, unsigned int height) {
    m_style = WindowStyle::Fixed;
    m_params.fixedX = x;
    m_params.fixedY = y;
    m_params.fixedWidth = width;
    m_params.fixedHeight = height;
}

WindowStyle Window::style() {
    return m_style;
}

const WindowStyleParams& Window::params() {
    return m_params;
}

void Window::refresh() {
    spdlog::debug("refresh called for {}", m_id);

    m_render->beginRender();
    m_render->clearBackground(m_baseWidget->fgColor(), m_baseWidget->bgColor());
    m_render->clearArea(m_baseWidget->x(), m_baseWidget->y(),
                        m_baseWidget->width(), m_baseWidget->height(),
                        m_baseWidget->fgColor(), m_baseWidget->bgColor());
    m_baseWidget->render(*m_render);
    m_render->endRender();
}

void Window::resize() {
    spdlog::info("resize called for {}", m_id);
    screen().curses().currentWindow(m_id);
    screen().curses().wresize(1, 1);
}

bool Window::contains(unsigned int x, unsigned int y) {
    if (x >= m_x && x <= (m_x + width())) {
        if (y >= m_y && y <= (m_y + height())) {
            return true;
        }
    }
    return false;
}

} // namespace SwearJar
