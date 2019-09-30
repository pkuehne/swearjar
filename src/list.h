#pragma once

#include "widget.h"

namespace SwearJar {

class List : public Widget {
public:
    List(const std::string& name);

    void addItem(std::string item);
    const std::vector<std::string>& items() { return m_items; }

    void itemOffset(unsigned int offset);
    unsigned int itemOffset() { return m_itemOffset; }

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;

private:
    std::vector<std::string> m_items;
    unsigned int m_itemOffset = 0;
};

} // namespace SwearJar
