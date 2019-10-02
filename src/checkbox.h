#pragma once

#include "widget.h"

namespace SwearJar {

class Checkbox : public Widget {
public:
    Checkbox(const std::string& name);

    void render(const RenderContext& context) override;
    bool handleKeyPress(const KeyEvent& event) override;
    bool handleMouseClick(const MouseEvent& event) override;

    std::function<void(Checkbox&)> onToggle;

    void text(const std::string& text);
    std::string text() { return m_text; }

    virtual void enabled(bool enabled);
    virtual bool enabled() { return m_enabled; }
    virtual void toggle() { enabled(!m_enabled); }

private:
    std::string m_text;
    bool m_enabled = false;
};

} // namespace SwearJar
