#include "window.h"
#include "screen.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Window::Window(Screen& s, unsigned int x, unsigned int y, unsigned int width,
               unsigned int height)
    : m_screen(s) {
    initialize();
    setWindowStyleFixed(x, y, width, height);
}

Window::Window(Screen& screen) : m_screen(screen) {
    initialize();
    resize();
}

Window::Window(Screen& screen, unsigned int width, unsigned int height)
    : m_screen(screen) {
    initialize();
    setWindowStyleFractional(width, height);
}

void Window::initialize() {
    m_id = screen().curses().newwin(1, 1, 0, 0);
    m_baseWidget = std::make_unique<BaseWidget>();
    m_render = std::make_unique<RenderContext>(screen().curses(), m_id);
}

Window::~Window() {
}

void Window::setWindowStyleFullScreen() {
    m_style = WindowStyle::FullScreen;
    resize();
}

void Window::setWindowStyleFractional(unsigned int widthFraction,
                                      unsigned int heightFraction) {
    m_style = WindowStyle::Fractional;
    m_params.fractionalWidth = widthFraction;
    m_params.fractionalHeight = heightFraction;
    resize();
}

void Window::setWindowStyleFixed(unsigned int x, unsigned int y,
                                 unsigned int width, unsigned int height) {
    m_style = WindowStyle::Fixed;
    m_params.fixedX = x;
    m_params.fixedY = y;
    m_params.fixedWidth = width;
    m_params.fixedHeight = height;
    resize();
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
    int screenHeight = 0, screenWidth = 0;
    screen().curses().get_screen_size(screenHeight, screenWidth);

    switch (style()) {
        case WindowStyle::FullScreen: {
            m_height = static_cast<unsigned int>(screenHeight);
            m_width = static_cast<unsigned int>(screenWidth);
            break;
        }
        case WindowStyle::Fractional: {
            m_width = screenWidth * m_params.fractionalWidth / 100;
            m_height = screenHeight * m_params.fractionalHeight / 100;

            m_x = (screenWidth / 2) - (m_width / 2);
            m_y = (screenHeight / 2) - (m_height / 2);
            spdlog::info("Resizing fractional to be @ ({}, {})", m_x, m_y);
            break;
        }
        case WindowStyle::Fixed: {
            m_width = m_params.fixedWidth;
            m_height = m_params.fixedHeight;
            m_x = m_params.fixedX;
            m_y = m_params.fixedY;
            break;
        }
        default: {
            spdlog::error("You must set a style!");
            screen().quit();
            break;
        }
    }

    screen().curses().currentWindow(m_id);
    screen().curses().mvwin(m_y, m_x);
    screen().curses().wresize(m_height, m_width);
    screen().curses().wrefresh();
    screen().curses().refresh();

    m_baseWidget->width(m_width);
    m_baseWidget->height(m_height);
    m_render->width(m_width);
    m_render->height(m_height);
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
