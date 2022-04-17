#include "checkbox.h"

namespace SwearJar {

Checkbox::Checkbox(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

void Checkbox::text(const std::wstring& text) {
    m_text = text;
    minWidth(text.size() + 4);
}

void Checkbox::text(const std::string& text) {
    this->text(convertString(text));
}

std::wstring Checkbox::text() {
    return m_text;
}

void Checkbox::enabled(bool enabled) {
    m_enabled = enabled;
}

bool Checkbox::enabled() {
    return m_enabled;
}

void Checkbox::toggle() {
    enabled(!m_enabled);
}

void Checkbox::render(const RenderContext& context) {
    context.drawText(0, 0, L"[ ] ", fgColor(), bgColor());
    context.drawText(4, 0, m_text, fgColor(), bgColor());

    if (enabled()) {
        context.drawChar(1, 0, L'X', fgColor(), bgColor());
    }
}

bool Checkbox::handleKeyPress(const KeyEvent& event) {
    if (event.key != 10) {
        return false;
    }

    toggle();

    if (onToggle != nullptr) {
        onToggle(*this);
    }
    return true;
}

bool Checkbox::handleMouseClick(const MouseEvent& /* event */) {
    toggle();

    if (onToggle != nullptr) {
        onToggle(*this);
    }
    return true;
}

} // namespace SwearJar
