#include "list.h"

namespace SwearJar {

List::List(const std::string& name) : Widget(name) { growthFactor(1); }
void List::addItem(std::string item) { m_items.push_back(item); }

void List::render(const RenderContext& context) {
    unsigned int y = 0;
    for (auto item : m_items) {
        context.drawText(0, y, item, fgColor(), bgColor());
        y++;
    }
}

} // namespace SwearJar
