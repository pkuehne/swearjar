#include "label.h"
#include <spdlog/spdlog.h>

namespace SwearJar {

Label::Label(const std::string& name) : Widget(name) {
}

void Label::text(const std::wstring& text) {
    minWidth(text.size());
    m_text = text;
}

void Label::centred(bool centred) {
    m_centred = centred;
}

void Label::render(const RenderContext& context) {
    context.drawText(0, 0, std::wstring(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = 0;
    if (m_centred) {
        xStart = (width() - m_text.length()) / 2;
    }
    context.drawText(xStart, 0, m_text, fgColor(), bgColor());
}

} // namespace SwearJar
