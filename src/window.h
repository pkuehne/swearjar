#pragma once
#include "curses_interface.h"
#include "layout_widget.h"
#include "render_context.h"
#include "screen.h"
#include <memory>
#include <vector>

namespace SwearJar {

class BaseWidget : public LayoutWidget {
public:
    BaseWidget() : LayoutWidget("base") {
    }
};

class Screen;

enum class WindowStyle {
    NoStyle,
    FullScreen,
    Fractional,
    Fixed,
};

struct WindowStyleParams {
    unsigned int fractionalWidth = 0;
    unsigned int fractionalHeight = 0;
    unsigned int fixedWidth = 0;
    unsigned int fixedHeight = 0;
    unsigned int fixedX = 0;
    unsigned int fixedY = 0;
};

class Window {
public:
    Window(Screen& screen);
    Window(Screen& screen, unsigned int width, unsigned int height);
    Window(Screen& screen, unsigned int x, unsigned int y, unsigned int width,
           unsigned int height);
    virtual ~Window();
    void initialize();

    BaseWidget& baseWidget() {
        return *m_baseWidget;
    }
    Screen& screen() {
        return m_screen;
    }
    unsigned int x() {
        return m_x;
    }
    unsigned int y() {
        return m_y;
    }
    unsigned int width() {
        return m_width;
    }
    unsigned int height() {
        return m_height;
    }
    bool contains(unsigned int x, unsigned int y);

    void setWindowStyleFullScreen();
    void setWindowStyleFractional(unsigned int widthFraction,
                                  unsigned int heightFraction);
    void setWindowStyleFixed(unsigned int x, unsigned int y, unsigned int width,
                             unsigned int height);
    WindowStyle style();
    const WindowStyleParams& params();

    void refresh();
    void resize();

private:
    unsigned int m_id = 0;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    Screen& m_screen;
    std::unique_ptr<BaseWidget> m_baseWidget;
    std::unique_ptr<RenderContext> m_render = 0;
    WindowStyle m_style = WindowStyle::NoStyle;
    WindowStyleParams m_params{};
};
}; // namespace SwearJar
