#pragma once
#include "widget.h"
#include <memory>
#include <vector>

namespace SwearJar {
class Panel {
public:
    Panel(unsigned int id);
    void addWidget(Widget* widget);
    void addWidget(std::shared_ptr<Widget> widget);

private:
    unsigned int m_id;
    std::vector<std::shared_ptr<Widget>> m_widgets;
};
}; // namespace SwearJar