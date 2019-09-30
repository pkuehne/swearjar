#include "list.h"
#include "spdlog/spdlog.h"

namespace SwearJar {

List::List(const std::string& name) : Widget(name) { growthFactor(1); }
void List::addItem(std::string item) { m_items.push_back(item); }

void List::itemOffset(unsigned int offset) {
    m_itemOffset = offset;
    unsigned int maxOffset = m_items.size() - height();
    if (m_itemOffset > maxOffset) {
        m_itemOffset = maxOffset;
    }
}

void List::render(const RenderContext& context) {
    unsigned int y = 0;
    auto item = m_items.begin() + m_itemOffset;
    for (; item != m_items.end(); item++) {
        if (y >= height()) {
            break;
        }
        context.drawText(0, y, *item, fgColor(), bgColor());
        y++;
    }
}

bool List::handleKeyPress(const KeyEvent& event) {
    if (event.key == KEY_DOWN) {
        itemOffset(m_itemOffset + 1);
    }
    if (event.key == KEY_UP) {
        itemOffset(m_itemOffset ? m_itemOffset - 1 : 0);
    }
}
} // namespace SwearJar
