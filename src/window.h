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
    unsigned int x() { return m_x; }
    unsigned int y() { return m_y; }
    unsigned int width() { return m_width; }
    unsigned int height() { return m_height; }
    bool contains(unsigned int x, unsigned int y);

    void refresh();

private:
    unsigned int m_id = 0;
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    Screen& m_screen;
    std::shared_ptr<CursesInterface> m_curses;
    std::unique_ptr<BaseWidget> m_baseWidget;
    std::unique_ptr<RenderContext> m_render = 0;
};
}; // namespace SwearJar
