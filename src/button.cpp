#include "button.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

Button::Button(const std::string& name) : Widget(name) { canTakeFocus(true); }

void Button::text(const std::string& text) {
    width(text.length() + 4);
    minWidth(text.length() + 4);
    m_text = text;
    dirty(true);
}

void Button::refresh(const RenderContext& render) {
    spdlog::debug("Button: Refreshing with {}", m_text);
    render.drawText(0, 0, std::string(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = (width() - m_text.length()) / 2;
    render.drawText(xStart, 0, m_text, fgColor(), bgColor());
    render.drawChar(0, 0, '<', fgColor(), bgColor());
    render.drawChar(width() - 1, 0, '>', fgColor(), bgColor());
}

bool Button::handleKeyPress(int ch) {
    spdlog::debug("Button '{}' pressed", name());
    if (ch != 10) {
        return false;
    }
    if (pressed != 0) {
        pressed(this);
    }
    return true;
}

} // namespace SwearJar
