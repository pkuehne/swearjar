#include "label.h"

namespace SwearJar {

Label::Label(const std::string& text) { this->text(text); }

void Label::text(const std::string& text) {
    width(text.length());
    m_text = text;
    dirty(true);
}

void Label::refresh(CIptr& curses) {
    drawText(0, 0, m_text, fgColor(), bgColor());
}

} // namespace SwearJar
