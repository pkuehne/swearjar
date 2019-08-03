#include "panel.h"

namespace SwearJar {

Panel::Panel(unsigned int id, CIptr curses, unsigned int height,
             unsigned int width)
    : m_id(id), m_curses(curses), m_height(height), m_width(width) {
    Widget::curses = curses;
    m_curses->currentWindow(m_id);
    curses->wbkgd(curses->get_color(7, 0));
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
    m_curses->currentWindow(m_id);
    for (auto widget : m_widgets) {
        if (!widget->dirty()) {
            continue;
        }
        widget->refresh();
        widget->dirty(false);
    }
    m_curses->wrefresh();
}

void Panel::clearPanel() {
    m_curses->currentWindow(m_id);
    m_curses->color_on(m_curses->get_color(7, 0));
    for (unsigned int y = 0; y < m_height; y++) {
        for (unsigned int x = 0; x < m_width; x++) {
            m_curses->mvaddch_(y, x, ' ');
        }
    }
    m_curses->color_off(m_curses->get_color(7, 2));
    m_curses->wrefresh();
}

} // namespace SwearJar