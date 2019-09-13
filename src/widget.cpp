#include "widget.h"
#include "spdlog/spdlog.h"

namespace SwearJar {

Widget::Widget(const std::string& name) : m_name(name) {}

void Widget::height(unsigned int height) {
    invalidate();
    m_height = height;
}

void Widget::minHeight(unsigned int height) {
    invalidate();
    m_minHeight = height;
}

void Widget::width(unsigned int width) {
    invalidate();
    m_width = width;
}

void Widget::minWidth(unsigned int width) {
    invalidate();
    m_minWidth = width;
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

void Widget::focus(bool focus) {
    m_hasFocus = focus;
    if (m_hasFocus && gainFocus != 0) {
        gainFocus(this);
    }
    if (!m_hasFocus && loseFocus != 0) {
        loseFocus(this);
    }
}

bool Widget::moveFocusForward() {
    if (canTakeFocus()) {
        invalidate();
        focus(!focus());
        return focus();
    }
    return false;
}

} // namespace SwearJar
