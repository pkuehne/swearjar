#include "window.h"
#include "logging.h"
#include "screen.h"
#include <iostream>

namespace SwearJar {

Window::Window(Screen& screen) : m_screen(screen) {
    LOG_INFO << L"Testing" << LOG_END;
    m_id = screen.curses().newwin(1, 1, 0, 0);
    m_baseWidget = std::make_unique<BaseWidget>();
    m_render = std::make_unique<RenderContext>(screen.curses(), m_id);
    resize();
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
    LOG_DEBUG << "refresh called for " << m_id << LOG_END;

    m_render->beginRender();
    m_render->clearBackground(m_baseWidget->fgColor(), m_baseWidget->bgColor());
    m_render->clearArea(m_baseWidget->x(), m_baseWidget->y(),
                        m_baseWidget->width(), m_baseWidget->height(),
                        m_baseWidget->fgColor(), m_baseWidget->bgColor());
    m_baseWidget->render(*m_render);
    m_render->endRender();
}

void Window::resize() {
    LOG_DEBUG << "resize called for " << m_id << LOG_END;
    int screenHeight = 0, screenWidth = 0;
    screen().curses().get_screen_size(screenHeight, screenWidth);

    switch (style()) {
        case WindowStyle::FullScreen: {
            m_height = static_cast<unsigned int>(screenHeight);
            m_width = static_cast<unsigned int>(screenWidth);
            m_x = 0;
            m_y = 0;
            break;
        }
        case WindowStyle::Fractional: {
            m_width = screenWidth * m_params.fractionalWidth / 100;
            m_height = screenHeight * m_params.fractionalHeight / 100;

            m_x = (screenWidth / 2) - (m_width / 2);
            m_y = (screenHeight / 2) - (m_height / 2);
            LOG_DEBUG << "Resizing fractional to be @ (" << m_x << ", " << m_y
                      << ")" << LOG_END;
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
            LOG_ERROR << "You must set a style!" << LOG_END;
            screen().quit();
            break;
        }
    }

    screen().curses().currentWindow(m_id);
    screen().curses().wresize(m_height, m_width);
    screen().curses().mvwin(m_y, m_x);

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
