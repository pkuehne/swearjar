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

    void enabled(bool enabled);
    bool enabled() { return m_enabled; }
    void toggle() { enabled(!m_enabled); }

private:
    std::string m_text;
    bool m_enabled = false;
};

} // namespace SwearJar
