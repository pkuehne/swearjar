#include "panel.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Panel::Panel(unsigned int id, CIptr curses, unsigned int height,
             unsigned int width)
    : m_id(id), m_curses(curses), m_baseWidget(std::make_shared<BaseWidget>()),
      m_height(height), m_width(width) {
    m_baseWidget->width(width);
    m_baseWidget->height(height);

    m_render = std::make_unique<RenderContext>(curses, id);
    m_render->width(width);
    m_render->height(height);

    clearPanel();
}

Panel::~Panel() {}

void Panel::addWidget(Widget* widget) {
    addWidget(std::shared_ptr<Widget>(widget));
}

void Panel::addWidget(std::shared_ptr<Widget> widget) {
    m_baseWidget->addWidget(widget);
}

void Panel::refreshDirtyWidgets() {
    m_render->beginRender();
    m_baseWidget->render(m_render);
    m_render->endRender();
}

void Panel::clearPanel() {
    spdlog::debug("clearPanel called");
    m_curses->currentWindow(m_id);
    m_curses->wbkgd(m_curses->get_color(7, 0));
}

} // namespace SwearJar
