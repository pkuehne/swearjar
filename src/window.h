#pragma once
#include "curses_interface.h"
#include "layout_widget.h"
#include "render_context.h"
#include <memory>
#include <vector>

namespace SwearJar {

class BaseWidget : public LayoutWidget {
public:
    BaseWidget() : LayoutWidget("base") {}
};

class Window {
public:
    Window(unsigned int id, CIptr curses, unsigned int height,
           unsigned int width);
    virtual ~Window();

    BaseWidget& baseWidget() { return *m_baseWidget; }

    void refreshDirtyWidgets();
    void clearWindow();

    unsigned int width() { return m_width; }
    unsigned int height() { return m_height; }

private:
    unsigned int m_id;
    std::shared_ptr<CursesInterface> m_curses;
    std::unique_ptr<BaseWidget> m_baseWidget;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    std::unique_ptr<RenderContext> m_render = 0;
};
}; // namespace SwearJar