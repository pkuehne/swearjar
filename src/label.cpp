#include "label.h"

namespace SwearJar {

Label::Label(const std::string& text) { this->text(text); }

void Label::text(const std::string& text) {
    width(text.length());
    m_text = text;
    dirty(true);
}

void Label::refresh(CIptr& curses) {
    drawText(0, 0, std::string(width(), ' '), fgColor(), bgColor());

    unsigned int xStart = 0;
    if (m_centred) {
        xStart = (width() - m_text.length()) / 2;
    }
    drawText(0, xStart, m_text, fgColor(), bgColor());
}

void Label::centered(bool centered) {
    m_centred = centered;
    dirty(true);
}

} // namespace SwearJar
