#pragma once

#include "curses_interface.h"

namespace SwearJar {

class RenderContext {
public:
<<<<<<< HEAD
    RenderContext(CursesInterface& curses, unsigned int window)
        : m_curses(curses), m_window(window) {
    }
=======
    RenderContext(CursesInterface& curses, unsigned int window);
>>>>>>> Move logging from render context
    virtual ~RenderContext() {
    }

    void window(unsigned int window) {
        m_window = window;
    }
    unsigned int window() {
        return m_window;
    }

    void width(unsigned int width) {
        m_width = width;
    }
    unsigned int width() {
        return m_width;
    }

    void height(unsigned int height) {
        m_height = height;
    }
    unsigned int height() {
        return m_height;
    }

    void xOffset(unsigned int xOffset) {
        m_xOffset = xOffset;
    }
    unsigned int xOffset() {
        return m_xOffset;
    }

    void yOffset(unsigned int yOffset) {
        m_yOffset = yOffset;
    }
    unsigned int yOffset() {
        return m_yOffset;
    }

    virtual void addOffsets(unsigned int x, unsigned int y) const {
        m_xOffset += x;
        m_yOffset += y;
    }
    virtual void clearOffsets(unsigned int x, unsigned int y) const {
        m_xOffset -= x;
        m_yOffset -= y;
    }

    virtual void reverse(bool on) const;
    virtual void blink(bool on) const;
    virtual void beginRender();
    virtual void endRender();
    virtual void clearBackground(short fg, short bg) const;
    virtual void drawText(unsigned int x, unsigned int y,
                          const std::string& text, short fg, short bg) const;
    virtual void drawText(unsigned int x, unsigned int y,
                          const std::wstring& text, short fg, short bg) const;
    virtual void drawChar(unsigned int x, unsigned int y, char ch) const;
    virtual void drawChar(unsigned int x, unsigned int y, wchar_t ch) const;
    virtual void drawChar(unsigned int x, unsigned int y, char ch, short fg,
                          short bg) const;
    virtual void drawChar(unsigned int x, unsigned int y, wchar_t ch, short fg,
                          short bg) const;

    virtual void clearArea(unsigned int x, unsigned int y, unsigned int width,
                           unsigned int height, short fg, short bg) const;
    virtual void drawBorder(unsigned int x, unsigned int y, unsigned int width,
                            unsigned int height, short fg, short bg) const;

private:
    CursesInterface& m_curses;
    unsigned int m_window = 0;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    mutable unsigned int m_xOffset = 0;
    mutable unsigned int m_yOffset = 0;
};

} // namespace SwearJar
