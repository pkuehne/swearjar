#include "widget.h"
#include "logging.h"

namespace SwearJar {

Widget::Widget(std::string name) : m_name(std::move(name)) {
}

Widget::~Widget() = default;

void Widget::height(unsigned int height) {
    m_height = height;
}
unsigned int Widget::height() {
    return m_height;
}

void Widget::minHeight(unsigned int height) {
    m_minHeight = height;
}

unsigned int Widget::requiredHeight() {
    return m_minHeight;
}

void Widget::width(unsigned int width) {
    m_width = width;
}
unsigned int Widget::width() {
    return m_width;
}

void Widget::minWidth(unsigned int width) {
    m_minWidth = width;
}
unsigned int Widget::requiredWidth() {
    return m_minWidth;
}

void Widget::x(unsigned int x) {
    m_x = x;
}

unsigned int Widget::x() {
    return m_x;
}

void Widget::y(unsigned int y) {
    m_y = y;
}
unsigned int Widget::y() {
    return m_y;
}

void Widget::fgColor(short fg) {
    m_fg = fg;
}

short Widget::fgColor() {
    return m_fg;
}

void Widget::bgColor(short bg) {
    m_bg = bg;
}

short Widget::bgColor() {
    return m_bg;
}

void Widget::growthFactor(unsigned int factor) {
    m_growthFactor = factor;
}

unsigned int Widget::growthFactor() {
    return m_growthFactor;
}

std::string Widget::name() {
    return m_name;
}

void Widget::focus(bool focus) {
    bool changed = focus != m_hasFocus;
    m_hasFocus = focus;
    if (changed && m_hasFocus && gainFocus != nullptr) {
        gainFocus(this);
    }
    if (changed && !m_hasFocus && loseFocus != nullptr) {
        loseFocus(this);
    }
}

void Widget::render(const RenderContext& /* context */) {
}

bool Widget::handleKeyPress(const KeyEvent& /* event */) {
    return true;
}
bool Widget::handleMouseClick(const MouseEvent& /* event */) {
    return true;
}

bool Widget::focus() {
    return m_hasFocus;
}
bool Widget::canTakeFocus() {
    return m_canTakeFocus;
}
void Widget::canTakeFocus(bool can) {
    m_canTakeFocus = can;
}

bool Widget::moveFocusForward() {
    if (canTakeFocus()) {
        focus(!focus());
        return focus();
    }
    return false;
}

} // namespace SwearJar
