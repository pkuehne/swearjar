#pragma once

#include "curses_interface.h"

namespace SwearJar {

class RenderContext {
public:
    RenderContext(CursesInterface& curses, unsigned int window);

    virtual ~RenderContext();

    void window(unsigned int window);
    unsigned int window();

    void width(unsigned int width);
    unsigned int width();

    void height(unsigned int height);
    unsigned int height();

    void xOffset(unsigned int xOffset);
    unsigned int xOffset();

    void yOffset(unsigned int yOffset);
    unsigned int yOffset();

    virtual void addOffsets(unsigned int x, unsigned int y) const;
    virtual void clearOffsets(unsigned int x, unsigned int y) const;

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
