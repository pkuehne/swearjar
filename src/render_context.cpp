#include "render_context.h"
#include "logging.h"

namespace SwearJar {

RenderContext::RenderContext(CursesInterface& curses, unsigned int window)
    : m_curses(curses), m_window(window) {
    LOG_DEBUG << "Created RenderContext for " << window << std::endl;
}

void RenderContext::window(unsigned int window) {
    m_window = window;
}

unsigned int RenderContext::window() {
    return m_window;
}

void RenderContext::width(unsigned int width) {
    m_width = width;
}

unsigned int RenderContext::width() {
    return m_width;
}

void RenderContext::height(unsigned int height) {
    m_height = height;
}

unsigned int RenderContext::height() {
    return m_height;
}

void RenderContext::xOffset(unsigned int xOffset) {
    m_xOffset = xOffset;
}

unsigned int RenderContext::xOffset() {
    return m_xOffset;
}

void RenderContext::yOffset(unsigned int yOffset) {
    m_yOffset = yOffset;
}

unsigned int RenderContext::yOffset() {
    return m_yOffset;
}

void RenderContext::addOffsets(unsigned int x, unsigned int y) const {
    m_xOffset += x;
    m_yOffset += y;
}

void RenderContext::clearOffsets(unsigned int x, unsigned int y) const {
    m_xOffset -= x;
    m_yOffset -= y;
}

void RenderContext::clearBackground(short fg, short bg) const {
    m_curses.wbkgd(m_curses.get_color(fg, bg));
}

void RenderContext::drawText(unsigned int x, unsigned int y,
                             const std::string& text, short fg,
                             short bg) const {
    m_curses.color_on(m_curses.get_color(fg, bg));
    m_curses.mvwprint(y + m_yOffset, x + m_xOffset, text);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawText(unsigned int x, unsigned int y,
                             const std::wstring& text, short fg,
                             short bg) const {
    m_curses.color_on(m_curses.get_color(fg, bg));
    m_curses.mvwprintw(y + m_yOffset, x + m_xOffset, text);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawChar(unsigned int x, unsigned int y, char ch) const {
    unsigned int xPos = m_xOffset + x;
    unsigned int yPos = m_yOffset + y;
    if (xPos > m_width || yPos > m_height) {
        LOG_WARN << "RC: Out of range " << xPos << " > " << m_width << " or "
                 << yPos << " > " << m_height << LOG_END;
        return;
    }
    m_curses.mvaddch_(yPos, xPos, ch);
}

void RenderContext::drawChar(unsigned int x, unsigned int y, wchar_t ch) const {
    unsigned int xPos = m_xOffset + x;
    unsigned int yPos = m_yOffset + y;
    if (xPos > m_width || yPos > m_height) {
        LOG_WARN << "RC: Out of range " << xPos << " > " << m_width << " or "
                 << yPos << " > " << m_height << LOG_END;
        return;
    }
    m_curses.mvaddwch_(yPos, xPos, ch);
}

void RenderContext::drawChar(unsigned int x, unsigned int y, char ch, short fg,
                             short bg) const {
    m_curses.color_on(m_curses.get_color(fg, bg));
    drawChar(x, y, ch);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawChar(unsigned int x, unsigned int y, wchar_t ch,
                             short fg, short bg) const {
    m_curses.color_on(m_curses.get_color(fg, bg));
    drawChar(x, y, ch);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::clearArea(unsigned int x, unsigned int y,
                              unsigned int width, unsigned int height, short fg,
                              short bg) const {
    if (width > m_width || height > m_height) {
        LOG_WARN << "RC: Invalid clear area " << width << "x" << height
                 << " @ (" << x << "," << y << ")" << LOG_END;
        return;
    }
    m_curses.color_on(m_curses.get_color(fg, bg));
    for (unsigned int yy = 0; yy < height; yy++) {
        for (unsigned int xx = 0; xx < width; xx++) {
            drawChar(xx + x, yy + y, ' ');
        }
    }
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawBorder(unsigned int x, unsigned int y,
                               unsigned int width, unsigned int height,
                               short fg, short bg) const {
    if (width < 3 || height < 3) {
        LOG_WARN << "RC: Invalid border dimensions " << width << "x" << height
                 << " @ (" << x << "," << y << ")" << LOG_END;
        return;
    }
    const wchar_t verticalBorder = L'│';
    const wchar_t horizontalBorder = L'─';
    const wchar_t cornerNW = L'┌';
    const wchar_t cornerNE = L'┐';
    const wchar_t cornerSW = L'└';
    const wchar_t cornerSE = L'┘';

    width -= 1;
    height -= 1;

    m_curses.color_on(m_curses.get_color(fg, bg));
    for (unsigned int yPos = 1; yPos < height; yPos++) {
        drawChar(x, yPos + y, verticalBorder);
        drawChar(x + width, yPos + y, verticalBorder);
    }

    for (unsigned int xPos = 1; xPos < width; xPos++) {
        drawChar(x + xPos, y, horizontalBorder);
        drawChar(x + xPos, y + height, horizontalBorder);
    }
    drawChar(x, y, cornerNW);
    drawChar(x + width, y, cornerNE);
    drawChar(x, y + height, cornerSW);
    drawChar(x + width, y + height, cornerSE);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::beginRender() {
    m_curses.currentWindow(m_window);
}

void RenderContext::endRender() {
    m_curses.touchwin_();
    m_curses.wrefresh();
}

void RenderContext::reverse(bool on) const {
    if (on) {
        m_curses.reverse_on();
    } else {
        m_curses.reverse_off();
    }
}

void RenderContext::blink(bool on) const {
    if (on) {
        m_curses.blink_on();
    } else {
        m_curses.blink_off();
    }
}

} // namespace SwearJar
