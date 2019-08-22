#pragma once

#include "dimension.h"
#include "render_context.h"
#include <memory>
#include <vector>

namespace SwearJar {

class Widget;
using WidgetP = std::shared_ptr<Widget>;
using WidgetV = std::vector<WidgetP>;

class Widget {
public: // Overridable
    Widget();
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

    virtual void refresh(const RenderContext& render);
    virtual bool handleKeyPress(int ch);

public: // Non-overridable
    void clearPrevDimension() { m_prevDimension = Dimension(); }
    Dimension prevDimension() const { return m_prevDimension; }

    const WidgetV& children() const { return m_widgets; }

    bool moveFocusForward();

    bool focus() { return m_hasFocus; }
    bool canTakeFocus() { return m_canTakeFocus; }
    std::function<void(Widget*)> gainFocus = 0;
    std::function<void(Widget*)> loseFocus = 0;

protected: // Internal widget functions
    void invalidate();
    void addWidget(WidgetP widget);
    void focus(bool focus);
    void canTakeFocus(bool can) { m_canTakeFocus = can; }

private:
    unsigned int m_panel;
    bool m_dirty = true;
    Dimension m_prevDimension;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    short m_fg = 8;
    short m_bg = 0;
    WidgetV m_widgets;
    WidgetV::iterator m_focusWidget;
    bool m_canTakeFocus = false;
    bool m_hasFocus = false;
};

} // namespace SwearJar
