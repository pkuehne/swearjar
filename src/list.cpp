#include "list.h"

namespace SwearJar {

List::List(const std::string& name) : Widget(name) {
    growthFactor(1);
    canTakeFocus(true);
}

void List::addItem(const std::wstring& item) {
    m_items.push_back(item);
}

void List::itemOffset(unsigned int offset) {
    m_itemOffset = offset;
    unsigned int maxOffset = m_items.size() - height();
    if (m_itemOffset > maxOffset) {
        m_itemOffset = maxOffset;
    }
    if (m_itemOffset > m_selectedItem) {
        selectedItem(m_itemOffset);
    }
    if (m_itemOffset + height() < m_selectedItem) {
        selectedItem(m_itemOffset + height() - 1);
    }
}

void List::selectedItem(unsigned int item) {
    unsigned int prevSelected = m_selectedItem;

    m_selectedItem = item;
    if (m_items.empty()) {
        m_selectedItem = 0;
    }
    if (m_selectedItem > m_items.size() - 1) {
        m_selectedItem = m_items.size() - 1;
    }
    if (m_selectedItem < m_itemOffset) {
        itemOffset(m_selectedItem);
    }
    if (m_selectedItem >= m_itemOffset + height()) {
        itemOffset(m_selectedItem);
    }
    if (prevSelected != m_selectedItem && onSelected) {
        onSelected(*this);
    }
}

void List::render(const RenderContext& context) {
    context.reverse(false);
    unsigned int y = 0;
    auto item = m_items.begin() + m_itemOffset;
    for (; item != m_items.end(); item++) {
        if (item - m_items.begin() == m_selectedItem) {
            context.reverse(focus());
        }
        if (y >= height()) {
            break;
        }
        context.drawText(0, y, *item, fgColor(), bgColor());
        y++;
        context.reverse(false);
    }
}

bool List::handleKeyPress(const KeyEvent& event) {
    if (event.key == KEY_PGDOWN) {
        itemOffset(m_itemOffset + 1);
        return true;
    }
    if (event.key == KEY_PGUP) {
        itemOffset(m_itemOffset != 0 ? m_itemOffset - 1 : 0);
        return true;
    }
    if (event.key == KEY_DOWN) {
        selectedItem(m_selectedItem + 1);
        return true;
    }
    if (event.key == KEY_UP) {
        selectedItem(m_selectedItem != 0 ? m_selectedItem - 1 : 0);
        return true;
    }
    if (event.key == KEY_ENTER) {
        if (onTriggered) {
            onTriggered(*this);
        }
        return true;
    }
    return false;
}
} // namespace SwearJar
