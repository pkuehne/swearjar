#pragma once

#include "widget.h"
#include <functional>

namespace SwearJar {

class TextEntry : public Widget {
public:
    explicit TextEntry(const std::string& name);

    void text(std::wstring text);
    std::wstring text();

    void cursor(unsigned int cursor);
    unsigned int cursor();

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

    std::function<void(TextEntry&)> onTextChanged = nullptr;
    std::function<void(TextEntry&)> onSubmit = nullptr;

private:
    std::wstring m_text;
    unsigned int m_cursor = 0;
};

} // namespace SwearJar
