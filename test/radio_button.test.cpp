#include "curses.mock.h"
#include "radio_button.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class RadioButtonWidget : public Test {
public:
    void SetUp() {
        button_one.group(&group);
        button_two.group(&group);
    }

protected:
    RadioButtonGroup group;
    RadioButtonGroup empty_group;
    RadioButton button_one{"btnOne"};
    RadioButton button_two{"btnTwo"};
    RadioButton button{"btnEmpty"};

    MouseEvent mouse;
    KeyEvent key;
};

TEST_F(RadioButtonWidget, addButtonToGroupIncreasesCount) {
    // Given

    // When
    empty_group.add(&button);

    // Then
    EXPECT_EQ(1, empty_group.buttons().size());
}

TEST_F(RadioButtonWidget, addButtonToGroupSetsGroupOnButton) {
    // Given

    // When
    empty_group.add(&button);

    // Then
    EXPECT_EQ(&empty_group, button.group());
}

TEST_F(RadioButtonWidget, settingGroupAddsButtonToGroup) {
    // Given

    // When
    button.group(&empty_group);

    // Then
    EXPECT_EQ(&empty_group, button.group());
    EXPECT_EQ(*empty_group.buttons().begin(), &button);
}

TEST_F(RadioButtonWidget, removeButtonFromGroupDecreasesCount) {
    // Given
    empty_group.add(&button);

    // When
    empty_group.remove(&button);

    // Then
    EXPECT_EQ(0, empty_group.buttons().size());
}

TEST_F(RadioButtonWidget, addingButtonToGroupUnGroupsFromPreviousGroup) {
    // Given
    RadioButtonGroup group_one;
    RadioButtonGroup group_two;
    RadioButton button("btnRadio");

    group_one.add(&button);

    // When
    group_two.add(&button);

    // Then
    EXPECT_EQ(&group_two, button.group());
    EXPECT_EQ(0, group_one.buttons().size());
    EXPECT_EQ(1, group_two.buttons().size());
}

TEST_F(RadioButtonWidget, settingGroupOnButtonRemovesItFromPreviousGroup) {
    // Given
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

TEST_F(RadioButtonWidget, toggleOnlyTurnsOn) {
    // Given
    button.group(&empty_group);

    // When
    button.toggle();
    EXPECT_TRUE(button.enabled());

    // Then
    button.toggle();
    EXPECT_TRUE(button.enabled());
}

TEST_F(RadioButtonWidget, enabledCanOnlyTurnOn) {
    // Given
    RadioButtonGroup empty_group;
    RadioButton button("btnRadio");
    button.group(&empty_group);

    // When
    button.enabled(true);
    EXPECT_TRUE(button.enabled());

    // Then
    button.enabled(false);
    EXPECT_TRUE(button.enabled());
}

TEST_F(RadioButtonWidget, enabledOneDisablesOthers) {
    // When
    button_one.enabled(true);
    button_two.enabled(true);

    // Then
    EXPECT_FALSE(button_one.enabled());
    EXPECT_TRUE(button_two.enabled());
    ASSERT_NE(group.current(), nullptr);
    EXPECT_EQ(group.current(), &button_two);
}

TEST_F(RadioButtonWidget, enablingButtonWithNoGroupHasNoEffect) {
    // When
    button.enabled(true);

    // Then
    EXPECT_FALSE(button.enabled());
}

TEST_F(RadioButtonWidget, settingCurrentMakesItEnabledOthersDisabled) {
    // Given

    // When
    group.current(&button_two);

    // Then
    EXPECT_FALSE(button_one.enabled());
    EXPECT_TRUE(button_two.enabled());
}

TEST_F(RadioButtonWidget, firstButtonAddedToGroupBecomesCurrent) {
    // Given

    // When

    // Then
    EXPECT_TRUE(button_one.enabled());
    EXPECT_FALSE(button_two.enabled());
}

TEST_F(RadioButtonWidget, removeButtonFromGroupSetsOtherToBeCurrent) {
    // Given

    // When
    group.remove(&button_one);

    // Then
    EXPECT_FALSE(button_one.enabled());
    EXPECT_TRUE(button_two.enabled());
}

TEST_F(RadioButtonWidget, removeLastButtonSetsCurrentToNull) {
    // Given
    empty_group.add(&button);

    // When
    empty_group.remove(&button);

    // Then
    EXPECT_EQ(nullptr, empty_group.current());
}

TEST_F(RadioButtonWidget, buttonWithNoGroupIsNotEnabled) {
    // Given

    // When
    bool enabled = button.enabled();

    // Then
    EXPECT_FALSE(enabled);
}

TEST_F(RadioButtonWidget, togglesWhenSelectionKeyPressed) {
    // Given
    key.key = 10;

    // When
    button_two.handleKeyPress(key);

    // Then
    EXPECT_TRUE(button_two.enabled());
}

TEST_F(RadioButtonWidget, togglesWhenClicked) {
    // Given

    // When
    button_two.handleMouseClick(mouse);

    // Then
    EXPECT_TRUE(button_two.enabled());
}

TEST_F(RadioButtonWidget, rendersIndicatorWhenEnabled) {
    // Given
    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('X'), _, _)).Times(1);

    // When
    button_one.render(*context);
}

TEST_F(RadioButtonWidget, doesntRenderIndicatorWhenNotEnabled) {
    // Given
    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('X'), _, _)).Times(0);

    // When
    button_two.render(*context);
}
