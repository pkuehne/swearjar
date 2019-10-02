#pragma once

#include "widget.h"

namespace SwearJar {

class TextEntry : public Widget {
public:
    TextEntry(const std::string& name);

    void text(std::string text);
    std::string text() {
        return m_text;
    }
    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

private:
    std::string m_text;
};

} // namespace SwearJar
