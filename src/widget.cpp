#include "widget.h"

namespace SwearJar {

CIptr Widget::curses;

void Widget::height(unsigned int height) {
    clearWidget();
    m_height = height;
    dirty(true);
}

void Widget::width(unsigned int width) {
    clearWidget();
    m_width = width;
    dirty(true);
}

void Widget::x(unsigned int x) {
    clearWidget();
    m_x = x;
    dirty(true);
}

void Widget::y(unsigned int y) {
    clearWidget();
    m_y = y;
    dirty(true);
}

void Widget::fgColor(short fg) {
    clearWidget();
    m_fg = fg;
    dirty(true);
}

void Widget::bgColor(short bg) {
    clearWidget();
    m_bg = bg;
    dirty(true);
}

void Widget::clearWidget() {
    if (dirty()) {
        return;
    }
    for (unsigned int y = m_y; y < m_height + m_y; y++) {
        for (unsigned int x = m_x; x < m_width + m_x; x++) {
            drawChar(y, x, ' ');
        }
    }
}

void Widget::drawText(unsigned int y, unsigned int x, const std::string& text,
                      short fg, short bg) {
    curses->color_on(curses->get_color(fg, bg));

    for (unsigned int offset = 0; offset < text.length(); offset++) {
        drawChar(m_y + y, m_x + x + offset, text[offset]);
    }
    curses->color_off(curses->get_color(fg, bg));
}

void Widget::drawChar(unsigned int y, unsigned int x, char ch, short fg,
                      short bg) {
    curses->color_on(curses->get_color(fg, bg));
    drawChar(y, x, ch);
    curses->color_off(curses->get_color(fg, bg));
}
void Widget::drawChar(unsigned int y, unsigned int x, char ch) {
    unsigned int xPos = m_x + x;
    unsigned int yPos = m_y + y;
    if (xPos > width() || yPos > height()) {
        return;
    }
    curses->mvaddch_(yPos, xPos, ch);
}

} // namespace SwearJar