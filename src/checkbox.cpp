#include "checkbox.h"

namespace SwearJar {

Checkbox::Checkbox(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

void Checkbox::text(const std::string& text) {
    m_text = text;
    width(text.size() + 4);
    invalidate();
}

void Checkbox::enabled(bool enabled) {
    m_enabled = enabled;
    invalidate();
}

void Checkbox::render(const RenderContext& context) {
    context.drawText(0, 0, "[ ] ", fgColor(), bgColor());
    context.drawText(4, 0, m_text, fgColor(), bgColor());

    if (m_enabled) {
        context.drawChar(1, 0, 'X', fgColor(), bgColor());
    }
}

bool Checkbox::handleKeyPress(int ch) {
    spdlog::debug("Checkbox '{}' toggled", name());
    if (ch != 10) {
        return false;
    }

    toggle();

    if (onToggle != 0) {
        onToggle(*this);
    }
    return true;
}
} // namespace SwearJar
