#include "radio_button.h"

namespace SwearJar {

void RadioButtonGroup::add(RadioButton* button) {
    m_buttons.insert(button);
    if (button->group() != this) {
        if (button->group() != nullptr) {
            button->group()->remove(button);
        }
        button->group(this);
    }
    if (m_current == nullptr) {
        m_current = button;
    }
}

void RadioButtonGroup::remove(RadioButton* button) {
    m_buttons.erase(button);
    if (button == m_current) {
        if (m_buttons.empty()) {
            m_current = nullptr;
        } else {
            m_current = *m_buttons.begin();
        }
    }
}

RadioButton* RadioButtonGroup::current() {
    return m_current;
}

void RadioButtonGroup::current(RadioButton* button) {
    if (m_current == button) {
        return;
    }
    m_current = button;
    if (onChanged && button != nullptr) {
        onChanged(*button);
    }
}

RadioButton::RadioButton(const std::string& name) : ToggleWidget(name) {
}

void RadioButton::group(RadioButtonGroup* group) {
    if (m_group != nullptr) {
        m_group->remove(this);
    }
    m_group = group;
    group->add(this);
}

bool RadioButton::enabled() {
    if (m_group == nullptr) {
        return false;
    }
    return m_group->current() == this;
}

void RadioButton::enabled(bool on) {
    if (m_group == nullptr || !on) {
        return;
    }
    m_group->current(this);
}

bool RadioButton::toggle() {
    if (enabled()) {
        return false;
    }
    enabled(true);
    return true;
}

void RadioButton::render(const RenderContext& context) {
    context.drawText(0, 0, L"( ) ", fgColor(), bgColor());
    context.drawText(4, 0, m_text, fgColor(), bgColor());
    if (enabled()) {
        context.drawChar(1, 0, L'*', fgColor(), bgColor());
    }
}

RadioButtonGroup* RadioButton::group() {
    return m_group;
}

} // namespace SwearJar
