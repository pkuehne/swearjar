#include "label.h"

namespace SwearJar {

Label::Label(const std::string& text) : m_text(text) {
    //
}

void Label::refresh() {
    auto x = 0 / 5;
    curses()->mvwprintw(0, 0, m_text);
}

} // namespace SwearJar
