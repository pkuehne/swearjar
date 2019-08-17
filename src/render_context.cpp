#include "render_context.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

void RenderContext::drawText(unsigned int x, unsigned int y,
                             const std::string& text, short fg,
                             short bg) const {

    spdlog::info("RC: drawing text {}", text);
    for (unsigned int offset = 0; offset < text.length(); offset++) {
        drawChar(x + offset, y, text[offset], fg, bg);
    }
}
void RenderContext::drawChar(unsigned int x, unsigned int y, char ch, short fg,
                             short bg) const {
    unsigned int xPos = m_xOffset + x;
    unsigned int yPos = m_yOffset + y;
    spdlog::info("RC: Placing {} at ({},{}) = ({},{})", ch, x, y, xPos, yPos);
    if (xPos > m_width || yPos > m_height) {
        spdlog::info("RC: Out of range {} > {} or {} > {}", xPos, m_width, yPos,
                     m_height);
        return;
    }
    m_curses->color_on(m_curses->get_color(fg, bg));
    m_curses->mvaddch_(yPos, xPos, ch);
    m_curses->color_off(m_curses->get_color(fg, bg));
}

void RenderContext::clearArea(unsigned int x, unsigned int y,
                              unsigned int width, unsigned int height, short fg,
                              short bg) const {

    if (width == 0 || height == 0) {
        return;
    }
    m_curses->color_on(m_curses->get_color(fg, bg));
    for (unsigned int y = 0; y < m_height; y++) {
        for (unsigned int x = 0; x < m_width; x++) {
            m_curses->mvaddch_(y, x, ' ');
        }
    }
    m_curses->color_off(m_curses->get_color(fg, bg));
}

void RenderContext::beginRender() {
    spdlog::info("Begin render for {}", m_panel);
    m_curses->currentWindow(m_panel);
}

void RenderContext::endRender() {
    spdlog::info("End render for {}", m_panel);
    m_curses->wrefresh();
}

} // namespace SwearJar
