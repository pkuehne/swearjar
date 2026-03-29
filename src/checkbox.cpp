#include "checkbox.h"

namespace SwearJar {

Checkbox::Checkbox(const std::string& name) : ToggleWidget(name) {
}

void Checkbox::enabled(bool enabled) {
    m_enabled = enabled;
}

bool Checkbox::enabled() {
    return m_enabled;
}

bool Checkbox::toggle() {
    enabled(!m_enabled);
    return true;
}

void Checkbox::render(const RenderContext& context) {
    context.drawText(0, 0, L"[ ] ", fgColor(), bgColor());
    context.drawText(4, 0, m_text, fgColor(), bgColor());
    if (enabled()) {
        context.drawChar(1, 0, L'X', fgColor(), bgColor());
    }
}

} // namespace SwearJar
