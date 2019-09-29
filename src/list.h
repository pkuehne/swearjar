#pragma once

#include "widget.h"

namespace SwearJar {

class List : public Widget {
public:
    List(const std::string& name);

    void addItem(std::string item);
    const std::vector<std::string>& items() { return m_items; }

private:
    std::vector<std::string> m_items;
};

} // namespace SwearJar
