#pragma once
#include "curses_interface.h"
#include "widget.h"
#include <memory>
#include <vector>

namespace SwearJar {
class Panel {
public:
    Panel(unsigned int id, std::shared_ptr<CursesInterface> curses);
    virtual ~Panel();
    void addWidget(Widget* widget);
    void addWidget(std::shared_ptr<Widget> widget);
    const std::vector<std::shared_ptr<Widget>>& widgets() { return m_widgets; }

    void refreshDirtyWidgets();

private:
    unsigned int m_id;
    std::shared_ptr<CursesInterface> m_curses;
    std::vector<std::shared_ptr<Widget>> m_widgets;
};
}; // namespace SwearJar