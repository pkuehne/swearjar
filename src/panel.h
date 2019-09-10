#pragma once
#include "layout_widget.h"
#include "curses_interface.h"
#include "render_context.h"
#include <memory>
#include <vector>

namespace SwearJar {

class BaseWidget : public LayoutWidget {
public:
    BaseWidget() : LayoutWidget("base") {}
};

class Panel {
public:
    Panel(unsigned int id, CIptr curses, unsigned int height,
          unsigned int width);
    virtual ~Panel();
    void addWidget(Widget* widget);
    void addWidget(std::shared_ptr<Widget> widget);
    template <typename T>
    std::shared_ptr<T> createWidget(const std::string& name, unsigned int x,
                                    unsigned int y) {
        return m_baseWidget->createWidget<T>(name, x, y);
    }

    WidgetP widget() { return m_baseWidget; }
    std::shared_ptr<BaseWidget> baseWidget() { return m_baseWidget; }
    const WidgetV& widgets() { return m_baseWidget->children(); }

    void refreshDirtyWidgets();
    void clearPanel();

    unsigned int width() { return m_width; }
    unsigned int height() { return m_height; }

private:
    unsigned int m_id;
    std::shared_ptr<CursesInterface> m_curses;
    std::shared_ptr<BaseWidget> m_baseWidget;
    unsigned int m_height = 1;
    unsigned int m_width = 1;
    RenderContext m_render;
};
}; // namespace SwearJar
