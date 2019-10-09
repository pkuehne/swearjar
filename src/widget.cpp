#include "widget.h"
#include "spdlog/spdlog.h"

namespace SwearJar {

Widget::Widget(const std::string& name) : m_name(name) {
}

void Widget::height(unsigned int height) {
    m_height = height;
}
unsigned int Widget::height() {
    return m_height;
}

void Widget::minHeight(unsigned int height) {
    m_minHeight = height;
}

unsigned int Widget::minHeight() {
    return m_minHeight;
}

unsigned int Widget::requiredHeight() {
    return m_minHeight;
}

void Widget::width(unsigned int width) {
    m_width = width;
}

void Widget::minWidth(unsigned int width) {
    m_minWidth = width;
}

void Widget::x(unsigned int x) {
    m_x = x;
}

void Widget::y(unsigned int y) {
    m_y = y;
}

void Widget::fgColor(short fg) {
    m_fg = fg;
}

void Widget::bgColor(short bg) {
    m_bg = bg;
}

void Widget::growthFactor(unsigned int factor) {
    m_growthFactor = factor;
}

void Widget::focus(bool focus) {
    bool changed = focus != m_hasFocus;
    m_hasFocus = focus;
    if (changed && m_hasFocus && gainFocus != 0) {
        gainFocus(this);
    }
    if (changed && !m_hasFocus && loseFocus != 0) {
        loseFocus(this);
    }
}

bool Widget::moveFocusForward() {
    if (canTakeFocus()) {
        focus(!focus());
        return focus();
    }
    return false;
}

} // namespace SwearJar
