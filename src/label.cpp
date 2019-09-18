#include "label.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

Label::Label(const std::string& name) : Widget(name) {}

void Label::text(const std::string& text) {
    width(text.length());
    minWidth(text.length());
    m_text = text;
}

void Label::centred(bool centred) {
    m_centred = centred;
    invalidate();
}

void Label::render(const RenderContext* context) {
    spdlog::debug("Rendering with {}", m_text);
    context->drawText(0, 0, std::string(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = 0;
    if (m_centred) {
        xStart = (width() - m_text.length()) / 2;
    }
    context->drawText(xStart, 0, m_text, fgColor(), bgColor());
}

} // namespace SwearJar
