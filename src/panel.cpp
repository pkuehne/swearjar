#include "panel.h"

namespace SwearJar {

Panel::Panel(unsigned int id) : m_id(id) {
    //
}

void Panel::addWidget(Widget* widget) {
    addWidget(std::shared_ptr<Widget>(widget));
}
void Panel::addWidget(std::shared_ptr<Widget> widget) {
    m_widgets.push_back(widget);
}

} // namespace SwearJar