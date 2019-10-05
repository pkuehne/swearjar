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
        if (m_buttons.size()) {
            m_current = *m_buttons.begin();
        } else {
            m_current = nullptr;
        }
    }
}
void RadioButtonGroup::current(RadioButton* button) {
    m_current = button;
}

RadioButton::RadioButton(const std::string& name) : Checkbox(name) {
    //
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
        // return Checkbox::enabled(); }
    }
    return m_group->current() == this;
}

void RadioButton::enabled(bool) {
    if (m_group == nullptr) {
        // Checkbox::enabled(on);
        return;
    }
    m_group->current(this);
}

void RadioButton::toggle() {
    this->enabled(true);
}

} // namespace SwearJar
