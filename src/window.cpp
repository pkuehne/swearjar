#include "window.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Window::Window(unsigned int id, CIptr curses, unsigned int height,
               unsigned int width)
    : m_id(id), m_curses(curses), m_height(height), m_width(width) {
    m_baseWidget = std::make_unique<BaseWidget>();
    m_baseWidget->width(width);
    m_baseWidget->height(height);

    m_render = std::make_unique<RenderContext>(curses, id);
    m_render->width(width);
    m_render->height(height);

    // clearWindow();
}

Window::~Window() {}

void Window::refreshDirtyWidgets() {
    spdlog::debug("refreshDirty called for {}", m_id);
    m_render->beginRender();
    m_baseWidget->render(*m_render);
    m_render->endRender();
}

void Window::clearWindow() {
    spdlog::debug("clearWindow called for {}", m_id);
    m_curses->currentWindow(m_id);
    m_curses->wbkgd(m_curses->get_color(m_fg, m_bg));
}

} // namespace SwearJar
