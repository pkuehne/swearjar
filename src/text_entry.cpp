#include "text_entry.h"
#include <cctype>

namespace SwearJar {

TextEntry::TextEntry(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

std::wstring TextEntry::text() {
    return m_text;
}

void TextEntry::text(const std::wstring& text) {
    m_text = text;
    minWidth(text.size());
    m_cursor = text.size();
    if (onTextChanged) {
        onTextChanged(*this);
    }
}

unsigned int TextEntry::cursor() {
    return m_cursor;
}

void TextEntry::cursor(unsigned int cursor) {
    if (cursor > text().size()) {
        cursor = text().size();
    }
    m_cursor = cursor;
}

void TextEntry::render(const RenderContext& context) {
    context.drawText(0, 0, text(), fgColor(), bgColor());
    for (unsigned int ii = text().size(); ii < width(); ii++) {
        context.drawChar(ii, 0, L'_', fgColor(), bgColor());
    }
    if (focus()) {
        context.blink(true);
        context.drawChar(m_cursor, 0, L'█', fgColor(), bgColor());
        context.blink(false);
    }
}

bool TextEntry::handleKeyPress(const KeyEvent& event) {
    if (event.key == KEY_BACKSPACE) {
        if (text().empty()) {
            return true;
        }
        m_text.erase(m_cursor - 1, 1);
        m_cursor -= 1;
        if (onTextChanged) {
            onTextChanged(*this);
        }
        return true;
    }
    if (event.key == KEY_LEFT) {
        m_cursor -= m_cursor != 0 ? 1 : 0;
        return true;
    }
    if (event.key == KEY_RIGHT) {
        m_cursor += m_cursor != text().size() ? 1 : 0;
        return true;
    }
    if (event.key == KEY_ENTER) {
        if (onSubmit) {
            onSubmit(*this);
        }
        return true;
    }
    if (std::isprint(event.key) != 0) {
        m_text.insert(m_cursor, 1, event.key);
        m_cursor += 1;
        if (onTextChanged) {
            onTextChanged(*this);
        }
        return true;
    }
    return false;
}

bool TextEntry::handleMouseClick(const MouseEvent& event) {
    cursor(event.x);
    return true;
}

} // namespace SwearJar
