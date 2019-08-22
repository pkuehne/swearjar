#include "render_context.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

void RenderContext::drawText(unsigned int x, unsigned int y,
                             const std::string& text, short fg,
                             short bg) const {

    spdlog::debug("RC: drawing text {}", text);
    m_curses->color_on(m_curses->get_color(fg, bg));
    for (unsigned int offset = 0; offset < text.length(); offset++) {
        drawChar(x + offset, y, text[offset]);
    }
    m_curses->color_off(m_curses->get_color(fg, bg));
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
    m_curses->mvaddch_(yPos, xPos, ch);
}

void RenderContext::drawChar(unsigned int x, unsigned int y, char ch, short fg,
                             short bg) const {
    m_curses->color_on(m_curses->get_color(fg, bg));
    drawChar(x, y, ch);
    m_curses->color_off(m_curses->get_color(fg, bg));
}

void RenderContext::clearArea(unsigned int x, unsigned int y,
                              unsigned int width, unsigned int height, short fg,
                              short bg) const {

    spdlog::debug("RC: clearing area {}x{} @ ({},{})", width, height, x, y);
    if (width == 0 || height == 0) {
        spdlog::warn("RC: Invalid clear area {}x{} @ ({},{})", width, height, x,
                     y);
        return;
    }
    m_curses->color_on(m_curses->get_color(fg, bg));
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            drawChar(x, y, ' ');
        }
    }
    m_curses->color_off(m_curses->get_color(fg, bg));
}

void RenderContext::beginRender() {
    spdlog::debug("Begin render for {}", m_panel);
    m_curses->currentWindow(m_panel);
}

void RenderContext::endRender() {
    spdlog::debug("End render for {}", m_panel);
    m_curses->wrefresh();
}

void RenderContext::reverse(bool on) const {
    if (on) {
        m_curses->reverse_on();
    } else {
        m_curses->reverse_off();
    }
}

} // namespace SwearJar
