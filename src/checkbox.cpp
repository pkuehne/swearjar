#include "checkbox.h"

namespace SwearJar {

Checkbox::Checkbox(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

void Checkbox::text(const std::wstring& text) {
    m_text = text;
    minWidth(text.size() + 4);
}

void Checkbox::enabled(bool enabled) {
    m_enabled = enabled;
}

void Checkbox::render(const RenderContext& context) {
    context.drawText(0, 0, L"[ ] ", fgColor(), bgColor());
    context.drawText(4, 0, m_text, fgColor(), bgColor());

    if (enabled()) {
        spdlog::info("Rendering X for box {}", name());
        context.drawChar(1, 0, L'X', fgColor(), bgColor());
    }
}

bool Checkbox::handleKeyPress(const KeyEvent& event) {
    spdlog::debug("Checkbox '{}' toggled", name());
    if (event.key != 10) {
        return false;
    }

    toggle();

    if (onToggle != 0) {
        onToggle(*this);
    }
    return true;
}

bool Checkbox::handleMouseClick(const MouseEvent& event) {
    spdlog::info("Checkbox '{}' clicked", name());
    toggle();

    if (onToggle != 0) {
        onToggle(*this);
    }
    return true;
}

} // namespace SwearJar
