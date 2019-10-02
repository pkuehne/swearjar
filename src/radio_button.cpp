#include "radio_button.h"

namespace SwearJar {

void RadioButtonGroup::add(RadioButton& button) {
    m_buttons.insert(&button);
    if (button.group() != this) {
        if (button.group() != nullptr) {
            button.group()->remove(button);
        }
        button.group(this);
    }
}

void RadioButtonGroup::remove(RadioButton& button) { m_buttons.erase(&button); }

RadioButton::RadioButton(const std::string& name) : Checkbox(name) {
    //
}

void RadioButton::group(RadioButtonGroup* group) {
    if (m_group != nullptr) {
        m_group->remove(*this);
    }
    m_group = group;
    group->add(*this);
}
} // namespace SwearJar
