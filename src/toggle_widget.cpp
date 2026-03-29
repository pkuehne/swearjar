#include "toggle_widget.h"

namespace SwearJar {

ToggleWidget::ToggleWidget(const std::string& name) : Widget(name) {
    canTakeFocus(true);
}

void ToggleWidget::text(const std::wstring& text) {
    m_text = text;
    minWidth(text.size() + 4);
}

void ToggleWidget::text(const std::string& text) {
    this->text(convertString(text));
}

std::wstring ToggleWidget::text() {
    return m_text;
}

bool ToggleWidget::handleKeyPress(const KeyEvent& event) {
    if (event.key != 10) {
        return false;
    }
    toggle();
    if (onToggle) {
        onToggle(*this);
    }
    return true;
}

bool ToggleWidget::handleMouseClick(const MouseEvent& /* event */) {
    toggle();
    if (onToggle) {
        onToggle(*this);
    }
    return true;
}

} // namespace SwearJar
