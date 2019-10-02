#include "text_entry.h"
#include <ctype.h>

namespace SwearJar {

TextEntry::TextEntry(const std::string& name) : Widget(name) {
}

void TextEntry::text(std::string text) {
    m_text = text;
}

void TextEntry::render(const RenderContext& context) {
    context.drawText(0, 0, text(), fgColor(), bgColor());
    for (int ii = text().size(); ii < width(); ii++) {
        context.drawChar(ii, 0, '_', fgColor(), bgColor());
    }
}

bool TextEntry::handleKeyPress(const KeyEvent& event) {
    if (event.key == KEY_BACKSPACE) {
        m_text.pop_back();
        return true;
    }
    if (std::isprint(event.key)) {
        m_text += event.key;
        return true;
    }
    return false;
}

bool TextEntry::handleMouseClick(const MouseEvent& event) {
}

} // namespace SwearJar
