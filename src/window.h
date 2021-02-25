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
    BaseWidget();
};

class Screen;

enum class WindowStyle {
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
    explicit Window(Screen& screen);
    virtual ~Window() = default;

    BaseWidget& baseWidget();

    Screen& screen();
    unsigned int x();
    unsigned int y();
    unsigned int width();
    unsigned int height();
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
    std::unique_ptr<RenderContext> m_render = nullptr;
    WindowStyle m_style = WindowStyle::FullScreen;
    WindowStyleParams m_params{};
};
} // namespace SwearJar
