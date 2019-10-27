#pragma once

#include "widget.h"

namespace SwearJar {

class Checkbox : public Widget {
public:
    explicit Checkbox(const std::string& name);

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

    std::function<void(Checkbox&)> onToggle;

    void text(const std::wstring& text);
    std::wstring text() {
        return m_text;
    }

    virtual void enabled(bool enabled);
    virtual bool enabled() {
        return m_enabled;
    }
    virtual void toggle() {
        enabled(!m_enabled);
    }

private:
    std::wstring m_text;
    bool m_enabled = false;
};

} // namespace SwearJar
