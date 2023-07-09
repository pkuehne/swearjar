#pragma once

#include "render_context.h"
#include <functional>
#include <memory>
#include <vector>

namespace SwearJar {

class Widget;

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
public:
    explicit Widget(const std::string& name);
    Widget(const Widget&) = delete;
    virtual ~Widget();

    static std::wstring convertString(const std::string& input);

    virtual void height(unsigned int height);
    virtual unsigned int height();
    virtual void minHeight(unsigned int height);
    virtual unsigned int requiredHeight();

    virtual void width(unsigned int width);
    virtual unsigned int width();
    virtual void minWidth(unsigned int width);
    virtual unsigned int requiredWidth();

    virtual void x(unsigned int x);
    virtual unsigned int x();
    virtual void y(unsigned int y);
    virtual unsigned int y();
    virtual void fgColor(short fg);
    virtual short fgColor();
    virtual void bgColor(short bg);
    virtual short bgColor();
    virtual void growthFactor(unsigned int factor);
    virtual unsigned int growthFactor();

    virtual const std::string& name();

    virtual void render(const RenderContext& /* context */);
    virtual bool handleKeyPress(const KeyEvent& /* event */);
    virtual bool handleMouseClick(const MouseEvent& /* event */);

    virtual bool moveFocusForward();

public: // Non-overridable
    bool focus();
    bool canTakeFocus();
    std::function<void(Widget*)> gainFocus = nullptr;
    std::function<void(Widget*)> loseFocus = nullptr;

protected: // Internal widget functions
    void focus(bool focus);
    void canTakeFocus(bool can);

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
