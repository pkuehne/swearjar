#include "label.h"

namespace SwearJar {

Label::Label(const std::string& name) : Widget(name) {
}

void Label::text(const std::wstring& text) {
    minWidth(text.size());
    m_text = text;
}

const std::wstring& Label::text() {
    return m_text;
}

void Label::centred(bool centred) {
    m_centred = centred;
}

bool Label::centred() {
    return m_centred;
}

void Label::render(const RenderContext& context) {
    context.clearArea(0, 0, width(), height(), fgColor(), bgColor());

    unsigned int xStart = 0;
    if (m_centred) {
        xStart = (width() - m_text.length()) / 2;
    }
    context.drawText(xStart, 0, m_text, fgColor(), bgColor());
}

} // namespace SwearJar
