#pragma once
#include "widget.h"
#include <string>

namespace SwearJar {

class Label : public Widget {
public:
    explicit Label(const std::string& text);
    void text(std::string& text) {
        m_text = text;
        dirty(true);
    }
    const std::string& text() { return m_text; }

    void refresh();

private:
    std::string m_text;
};

} // namespace SwearJar