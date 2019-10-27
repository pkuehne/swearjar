#pragma once

#include "widget.h"
#include <functional>

namespace SwearJar {

class List : public Widget {
public:
    explicit List(const std::string& name);

    void addItem(const std::wstring& item);
    const std::vector<std::wstring>& items() {
        return m_items;
    }

    void itemOffset(unsigned int offset);
    unsigned int itemOffset() {
        return m_itemOffset;
    }

    void selectedItem(unsigned int item);
    unsigned int selectedItem() {
        return m_selectedItem;
    }

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;

    std::function<void(List&)> onSelected = nullptr;
    std::function<void(List&)> onTriggered = nullptr;

private:
    std::vector<std::wstring> m_items;
    unsigned int m_itemOffset = 0;
    unsigned int m_selectedItem = 0;
};

} // namespace SwearJar
