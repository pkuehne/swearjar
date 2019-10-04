#include "button.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

Button::Button(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

void Button::text(const std::wstring& text) {
    minWidth(text.length() + 4);
    m_text = text;
}

void Button::render(const RenderContext& context) {
    context.drawText(0, 0, std::wstring(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = (width() - m_text.length()) / 2;
    context.drawText(xStart, 0, m_text, fgColor(), bgColor());
    context.drawChar(0, 0, '<', fgColor(), bgColor());
    context.drawChar(width() - 1, 0, '>', fgColor(), bgColor());
}

bool Button::handleKeyPress(const KeyEvent& event) {
    spdlog::debug("Button '{}' pressed", name());
    if (event.key != 10) {
        return false;
    }
    if (onPressed != 0) {
        onPressed(*this);
    }
    return true;
}

bool Button::handleMouseClick(const MouseEvent& event) {
    spdlog::info("Button '{}' clicked", name());
    if (onPressed != 0) {
        onPressed(*this);
    }
    return true;
}

} // namespace SwearJar
