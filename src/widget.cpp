#include "widget.h"

namespace SwearJar {

void Widget::height(unsigned int height) {
    invalidate();
    m_height = height;
}

void Widget::width(unsigned int width) {
    invalidate();
    m_width = width;
}

void Widget::x(unsigned int x) {
    invalidate();
    m_x = x;
}

void Widget::y(unsigned int y) {
    invalidate();
    m_y = y;
}

void Widget::fgColor(short fg) {
    invalidate();
    m_fg = fg;
}

void Widget::bgColor(short bg) {
    invalidate();
    m_bg = bg;
}

void Widget::invalidate() {
    if (dirty()) {
        return;
    }
    dirty(true);
    m_prevDimension = Dimension{m_x, m_y, m_width, m_height};
}

} // namespace SwearJar
