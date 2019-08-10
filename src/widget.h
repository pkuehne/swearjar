#pragma once

#include "curses_interface.h"
#include <memory>

namespace SwearJar {

class Widget {
    friend class Panel;

public:
    virtual ~Widget() {}
    virtual void dirty(bool value) { m_dirty = value; }
    virtual bool dirty() { return m_dirty; }

    virtual void height(unsigned int height);
    virtual unsigned int height() { return m_height; }
    virtual void width(unsigned int width);
    virtual unsigned int width() { return m_width; }
    virtual void x(unsigned int x);
    virtual unsigned int x() { return m_x; }
    virtual void y(unsigned int y);
    virtual unsigned int y() { return m_y; }
    virtual void fgColor(short fg);
    virtual short fgColor() { return m_fg; }
    virtual void bgColor(short bg);
    virtual short bgColor() { return m_bg; }

protected:
    virtual void refresh() {}

    virtual void clearWidget();
    void drawText(unsigned int y, unsigned int x, const std::string& text,
                  short fg, short bg);
    void drawChar(unsigned int y, unsigned int x, char ch, short fg, short bg);
    void drawChar(unsigned int y, unsigned int x, char ch);

protected:
    static CIptr curses;

private:
    bool m_dirty = true;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    short m_fg = 7;
    short m_bg = 0;
};

} // namespace SwearJar