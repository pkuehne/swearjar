#pragma once
#include "widget.h"
#include <string>

namespace SwearJar {

class Label : public Widget {
public:
    void text(std::string& text) { m_text = text; }
    const std::string& text() { return m_text; }

private:
    std::string m_text;
};

} // namespace SwearJar