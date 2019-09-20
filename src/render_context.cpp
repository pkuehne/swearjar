#include "render_context.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

void RenderContext::clearBackground(short fg, short bg) const {
    m_curses.wbkgd(m_curses.get_color(fg, bg));
}

void RenderContext::drawText(unsigned int x, unsigned int y,
                             const std::string& text, short fg,
                             short bg) const {

    spdlog::debug("RC: drawing text {}", text);
    m_curses.color_on(m_curses.get_color(fg, bg));
    for (unsigned int offset = 0; offset < text.length(); offset++) {
        drawChar(x + offset, y, text[offset]);
    }
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawChar(unsigned int x, unsigned int y, char ch) const {
    unsigned int xPos = m_xOffset + x;
    unsigned int yPos = m_yOffset + y;
    spdlog::debug("RC: Placing '{}' at ({},{}) = ({},{})", ch, x, y, xPos,
                  yPos);
    if (xPos > m_width || yPos > m_height) {
        spdlog::warn("RC: Out of range {} > {} or {} > {}", xPos, m_width, yPos,
                     m_height);
        return;
    }
    m_curses.mvaddch_(yPos, xPos, ch);
}

void RenderContext::drawChar(unsigned int x, unsigned int y, char ch, short fg,
                             short bg) const {
    m_curses.color_on(m_curses.get_color(fg, bg));
    drawChar(x, y, ch);
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::clearArea(unsigned int x, unsigned int y,
                              unsigned int width, unsigned int height, short fg,
                              short bg) const {

    spdlog::debug("RC: clearing area {}x{} @ ({},{})", width, height, x, y);
    if (width == 0 || height == 0) {
        spdlog::debug("RC: Invalid clear area {}x{} @ ({},{})", width, height,
                      x, y);
        return;
    }
    m_curses.color_on(m_curses.get_color(fg, bg));
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            drawChar(x, y, ' ');
        }
    }
    m_curses.color_off(m_curses.get_color(fg, bg));
}

void RenderContext::drawBorder(unsigned int x, unsigned int y,
                               unsigned int width, unsigned int height,
                               short fg, short bg) const {
    spdlog::debug("RC: drawing border {}x{} @ ({},{})", width, height, x, y);
    if (width < 3 || height < 3) {
        spdlog::warn("RC: Invalid border dimensions {}x{} @ ({},{})", width,
                     height, x, y);
        return;
    }
    const char verticalBorder = '|';
    const char horizontalBorder = '-';
    const char cornerNW = '+';
    const char cornerNE = '+';
    const char cornerSW = '+';
    const char cornerSE = '+';

    // const char verticalBorder = 186;
    // const char horizontalBorder = 205;
    // const char cornerNW = 201;
    // const char cornerNE = 187;
    // const char cornerSW = 200;
    // const char cornerSE = 188;

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
    m_curses.color_off(m_curses.get_color(bg, bg));
}

void RenderContext::beginRender() {
    spdlog::debug("Begin render for {}", m_window);
    m_curses.currentWindow(m_window);
}

void RenderContext::endRender() {
    spdlog::debug("End render for {}", m_window);
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

} // namespace SwearJar
