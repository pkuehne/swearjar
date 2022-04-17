#pragma once

#include "widget.h"

namespace SwearJar {
class Button : public Widget {
public:
    explicit Button(const std::string& name);
    virtual void text(const std::wstring& text);
    virtual void text(const std::string& text);
    virtual const std::wstring& text();

    std::function<void(Button&)> onPressed;

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

private:
    std::wstring m_text;
};
} // namespace SwearJar
