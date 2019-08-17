#include "button.h"

namespace SwearJar {

Button::Button(const std::string& text) {
    this->text(text);
    height(3);
}

void Button::text(const std::string& text) {
    width(text.length() + 4);
    m_text = text;
    dirty(true);
}

void Button::refresh(const RenderContext& render) {
    render.drawText(0, 0, std::string(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = (width() - m_text.length()) / 2;
    render.drawText(xStart, 0, m_text, fgColor(), bgColor());
    render.drawChar(0, 0, '<', fgColor(), bgColor());
    render.drawChar(width() - 1, 0, '>', fgColor(), bgColor());
}

} // namespace SwearJar
