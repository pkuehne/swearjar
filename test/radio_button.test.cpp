#include "radio_button.h"
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class RadioButtonWidget : public Test {
public:
    void SetUp() {}

protected:
};

TEST_F(RadioButtonWidget, addButtonToGroupIncreasesCount) {
    // Given
    RadioButtonGroup group;
    RadioButton button("btnRadio");

    // When
    group.add(button);

    // Then
    EXPECT_EQ(1, group.buttons().size());
}

TEST_F(RadioButtonWidget, addButtonToGroupSetsGroupOnButton) {
    // Given
    RadioButtonGroup group;
    RadioButton button("btnRadio");

    // When
    group.add(button);

    // Then
    EXPECT_EQ(&group, button.group());
}

TEST_F(RadioButtonWidget, settingGroupAddsButtonToGroup) {
    // Given
    RadioButtonGroup group;
    RadioButton button("btnRadio");

    // When
    button.group(&group);

    // Then
    EXPECT_EQ(&group, button.group());
    EXPECT_EQ(*group.buttons().begin(), &button);
}

TEST_F(RadioButtonWidget, removeButtonFromGroupDecreasesCount) {
    // Given
    RadioButtonGroup group;
    RadioButton button("btnRadio");
    group.add(button);

    // When
    group.remove(button);

    // Then
    EXPECT_EQ(0, group.buttons().size());
}

TEST_F(RadioButtonWidget, addingButtonToGroupUnGroupsFromPreviousGroup) {
    RadioButtonGroup group_one;
    RadioButtonGroup group_two;
    RadioButton button("btnRadio");

    group_one.add(button);

    // When
    group_two.add(button);

    // Then
    EXPECT_EQ(&group_two, button.group());
    EXPECT_EQ(0, group_one.buttons().size());
    EXPECT_EQ(1, group_two.buttons().size());
}

TEST_F(RadioButtonWidget, settingGroupOnButtonRemovesItFromPreviousGroup) {
    RadioButtonGroup group_one;
    RadioButtonGroup group_two;
    RadioButton button("btnRadio");

    button.group(&group_one);

    // When
    button.group(&group_two);

    // Then
    EXPECT_EQ(&group_two, button.group());
    EXPECT_EQ(0, group_one.buttons().size());
    EXPECT_EQ(1, group_two.buttons().size());
}
