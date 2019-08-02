#include "panel.h"

namespace SwearJar {

Panel::Panel(unsigned int id, std::shared_ptr<CursesInterface> curses)
    : m_id(id), m_curses(curses) {
    Widget::curses = curses;
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

} // namespace SwearJar