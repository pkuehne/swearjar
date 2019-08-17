#include "panel.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Panel::Panel(unsigned int id, CIptr curses, unsigned int height,
             unsigned int width)
    : m_id(id), m_curses(curses), m_height(height), m_width(width),
      m_render(curses, id) {
    m_render.width(width);
    m_render.height(height);
    clearPanel();
}

Panel::~Panel() {}

void Panel::addWidget(Widget* widget) {
    addWidget(std::shared_ptr<Widget>(widget));
}
void Panel::addWidget(std::shared_ptr<Widget> widget) {
    m_widgets.push_back(widget);
}

void Panel::refreshDirtyWidgets() {
    spdlog::info("refreshDirtyWidgets called");

    // Clear previous position for the widget
    m_render.beginRender();
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        spdlog::info("clearing");
        Dimension d = widget->prevDimension();
        spdlog::info("Clearing area {}-{} {}-{}", d.x, d.y, d.width, d.height);
        m_render.clearArea(d.x, d.y, d.width, d.height, 7, 0);
    }

    // Re-render the widget
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        spdlog::info("refreshing");
        widget->refresh(m_render);
        widget->dirty(false);
    }
    m_render.endRender();
}

void Panel::clearPanel() {
    spdlog::info("clearPanel called");
    m_curses->currentWindow(m_id);
    m_curses->wbkgd(m_curses->get_color(7, 0));
}

} // namespace SwearJar
