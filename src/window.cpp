#include "window.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Window::Window(CIptr curses, unsigned int x, unsigned int y, unsigned int width,
               unsigned int height)
    : m_id(0), m_curses(curses) {

    m_id = m_curses->newwin(height, width, y, x);

    m_baseWidget = std::make_unique<BaseWidget>();
    m_baseWidget->width(width);
    m_baseWidget->height(height);

    m_render = std::make_unique<RenderContext>(curses, m_id);
    m_render->width(width);
    m_render->height(height);
}

Window::~Window() {}

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

} // namespace SwearJar
