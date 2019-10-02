#pragma once
#include "checkbox.h"
#include <set>

namespace SwearJar {

class RadioButton;
class RadioButtonGroup {
public:
    RadioButtonGroup() {}
    void add(RadioButton* button);
    void remove(RadioButton* button);
    std::set<RadioButton*> buttons() { return m_buttons; }

    void current(RadioButton* button);
    RadioButton* current() { return m_current; }

private:
    std::set<RadioButton*> m_buttons;
    RadioButton* m_current = nullptr;
};

class RadioButton : public Checkbox {
public:
    RadioButton(const std::string& name);

    bool enabled() override;
    void enabled(bool on) override;
    void toggle() override;

    void group(RadioButtonGroup* group);
    RadioButtonGroup* group() { return m_group; }

private:
    std::string m_title;
    RadioButtonGroup* m_group = nullptr;
};

} // namespace SwearJar
