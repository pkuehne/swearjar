#pragma once

#include "widget.h"
#include <functional>

namespace SwearJar {

class List : public Widget {
public:
    List(const std::string& name);

    void addItem(std::string item);
    const std::vector<std::string>& items() { return m_items; }

    void itemOffset(unsigned int offset);
    unsigned int itemOffset() { return m_itemOffset; }

    void selectedItem(unsigned int item);
    unsigned int selectedItem() { return m_selectedItem; }

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;

    std::function<void(List&)> onSelected = nullptr;
    std::function<void(List&)> onTriggered = nullptr;

private:
    std::vector<std::string> m_items;
    unsigned int m_itemOffset = 0;
    unsigned int m_selectedItem = 0;
};

} // namespace SwearJar