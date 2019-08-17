#pragma once

#include "curses_interface.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

class RenderContext {

public:
    RenderContext(CIptr& curses, unsigned int panel)
        : m_curses(curses), m_panel(panel) {
            spdlog::info("Created RenderContext for {}", panel);
        }

    void panel(unsigned int panel) { m_panel = panel; }
    unsigned int panel() { return m_panel; }

    void width(unsigned int width) { m_width = width; }
    unsigned int width() { return m_width; }

    void height(unsigned int height) { m_height = height; }
    unsigned int height() { return m_height; }

    void xOffset(unsigned int xOffset) { m_xOffset = xOffset; }
    unsigned int xOffset() { return m_xOffset; }

    void yOffset(unsigned int yOffset) { m_yOffset = yOffset; }
    unsigned int yOffset() { return m_yOffset; }

    void beginRender();
    void endRender();
    void drawText(unsigned int x, unsigned int y, const std::string& text,
                  short fg, short bg) const;
    void drawChar(unsigned int x, unsigned int y, char ch, short fg, short bg) const;
    void clearArea(unsigned int x, unsigned int y, unsigned int width,
                   unsigned int height, short fg, short bg) const;

private:
    CIptr m_curses;
    unsigned int m_panel;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_xOffset;
    unsigned int m_yOffset;
};

} // namespace SwearJar
