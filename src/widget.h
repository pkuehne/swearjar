#pragma once

#include "dimension.h"
#include "render_context.h"
#include <memory>

namespace SwearJar {

class Widget {
public: // Overridable
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

    virtual void refresh(const RenderContext& render) {}

public: // Non-overridable
    void clearPrevDimensions() { m_prevDimension = Dimension(); }
    Dimension prevDimension() { return m_prevDimension; }

protected: // Internal widget functions
    void invalidate();

private:
    unsigned int m_panel;
    bool m_dirty = true;
    Dimension m_prevDimension;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    short m_fg = 7;
    short m_bg = 0;
};

} // namespace SwearJar
