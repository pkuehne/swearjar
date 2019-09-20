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
    BaseWidget() : LayoutWidget("base") {}
};

class Screen;

class Window {
public:
    Window(Screen& screen, unsigned int x, unsigned int y, unsigned int width,
           unsigned int height);
    virtual ~Window();

    BaseWidget& baseWidget() { return *m_baseWidget; }
    Screen& screen() { return m_screen; }

    void refresh();

private:
    unsigned int m_id = 0;
    Screen& m_screen;
    std::shared_ptr<CursesInterface> m_curses;
    std::unique_ptr<BaseWidget> m_baseWidget;
    std::unique_ptr<RenderContext> m_render = 0;
};
}; // namespace SwearJar
