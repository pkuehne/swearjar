#pragma once
#include "curses_interface.h"
#include "render_context.h"
#include "widget.h"
#include <memory>
#include <vector>

namespace SwearJar {

class BaseWidget : public Widget {
public:
    void addWidget(WidgetP widget) { Widget::addWidget(widget); }
};

class Panel {
public:
    Panel(unsigned int id, CIptr curses, unsigned int height,
          unsigned int width);
    virtual ~Panel();
    void addWidget(Widget* widget);
    void addWidget(std::shared_ptr<Widget> widget);
    template <typename T> WidgetP createWidget() {
        auto w = std::make_shared<T>();
        addWidget(w);
        return w;
    }

    WidgetP widget() { return m_baseWidget; }
    const WidgetV& widgets() { return m_baseWidget->children(); }

    void refreshDirtyWidgets();
    void clearPanel();

private:
    unsigned int m_id;
    std::shared_ptr<CursesInterface> m_curses;
    std::shared_ptr<BaseWidget> m_baseWidget;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    RenderContext m_render;
};
}; // namespace SwearJar
