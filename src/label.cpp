#include "label.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

Label::Label(const std::string& name) : Widget(name) {}

void Label::text(const std::string& text) {
    width(text.length());
    minWidth(text.length());
    m_text = text;
}

void Label::refresh(const RenderContext& render) {
    spdlog::debug("Refreshing with {}", m_text);
    render.drawText(0, 0, std::string(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = 0;
    if (m_centred) {
        xStart = (width() - m_text.length()) / 2;
    }
    render.drawText(xStart, 0, m_text, fgColor(), bgColor());
}

void Label::centered(bool centered) {
    m_centred = centered;
    dirty(true);
}

} // namespace SwearJar
