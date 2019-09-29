#pragma once

#include "render_context.h"
#include <functional>
#include <memory>
#include <vector>

namespace SwearJar {

class Widget;
using WidgetP = std::shared_ptr<Widget>;
using WidgetV = std::vector<WidgetP>;

using RenderContextP = std::unique_ptr<RenderContext>;

enum Color {
    Red = 1,
    Green = 2,
    Yellow = 3,
    Blue = 4,
    Magenta = 5,
    Cyan = 6,
    White = 7,
    Grey = 8,
    Black = 16,
};

class Widget {
public: // Overridable
    Widget(const std::string& name);
    Widget(Widget&) = delete;
    virtual ~Widget() {}

    virtual void height(unsigned int height);
    virtual unsigned int height() { return m_height; }
    virtual void minHeight(unsigned int height);
    virtual unsigned int minHeight() { return m_minHeight; }

    virtual void width(unsigned int width);
    virtual unsigned int width() { return m_width; }
    virtual void minWidth(unsigned int width);
    virtual unsigned int minWidth() { return m_minWidth; }

    virtual void x(unsigned int x);
    virtual unsigned int x() { return m_x; }
    virtual void y(unsigned int y);
    virtual unsigned int y() { return m_y; }
    virtual void fgColor(short fg);
    virtual short fgColor() { return m_fg; }
    virtual void bgColor(short bg);
    virtual short bgColor() { return m_bg; }
    virtual void growthFactor(unsigned int factor);
    virtual unsigned int growthFactor() { return m_growthFactor; }

    virtual std::string name() { return m_name; }

    virtual void render(const RenderContext& context) {}

    virtual bool handleKeyPress(const KeyEvent& event) { return true; }
    virtual bool handleMouseClick(const MouseEvent& event) { return true; }

public: // Non-overridable
    virtual bool moveFocusForward();

    bool focus() { return m_hasFocus; }
    bool canTakeFocus() { return m_canTakeFocus; }
    std::function<void(Widget*)> gainFocus = 0;
    std::function<void(Widget*)> loseFocus = 0;

protected: // Internal widget functions
    void focus(bool focus);
    void canTakeFocus(bool can) { m_canTakeFocus = can; }

private:
    std::string m_name;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    unsigned int m_minHeight = 1;
    unsigned int m_minWidth = 1;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    unsigned int m_growthFactor = 0;
    short m_fg = Color::White;
    short m_bg = Color::Black;
    bool m_canTakeFocus = false;
    bool m_hasFocus = false;
};

} // namespace SwearJar
