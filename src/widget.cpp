#include "widget.h"

namespace SwearJar {

CIptr Widget::curses;

void Widget::height(unsigned int height) {
    clearWidget();
    m_height = height;
}

void Widget::width(unsigned int width) {
    clearWidget();
    m_width = width;
}

void Widget::x(unsigned int x) {
    clearWidget();
    m_x = x;
}

void Widget::y(unsigned int y) {
    clearWidget();
    m_y = y;
}

void Widget::clearWidget() {
    if (dirty()) {
        return;
    }
    for (unsigned int y = m_y; y < m_height + m_y; y++) {
        for (unsigned int x = m_x; x < m_width + m_x; x++) {
            curses->mvaddch_(y, x, ' ');
        }
    }
}

} // namespace SwearJar