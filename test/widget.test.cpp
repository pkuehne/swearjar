#include "widget.h"
#include <gtest/gtest.h>

using namespace SwearJar;

class TestWidget : public SwearJar::Widget {
public:
    TestWidget() : Widget("") { canTakeFocus(true); }
    virtual ~TestWidget() {}
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
    void focus(bool focus) { Widget::focus(focus); }
    bool focus() { return Widget::focus(); }
};

TEST(Widget, moveFocusReturnsFalseWhenNoChildrenAndCantTakeFocus) {
    // Given
    TestWidget base;
    base.canTakeFocus(false);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
}

TEST(Widget, moveFocusReturnsFalseIfAlreadyHasFocus) {
    // Given
    TestWidget base;
    base.focus(true);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(base.focus());
}

TEST(Widget, gainFocusCalledWhenFocusSetToTrue) {
    // Given
    TestWidget base;
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&](Widget*) { gain_called = true; };
    base.loseFocus = [&](Widget*) { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(true));

    // Then
    EXPECT_TRUE(gain_called);
    EXPECT_FALSE(lose_called);
}

TEST(Widget, loseFocusFunctionCalledWhenFocusSetFalse) {
    // Given
    TestWidget base;
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&](Widget*) { gain_called = true; };
    base.loseFocus = [&](Widget*) { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(false));

    // Then
    EXPECT_FALSE(gain_called);
    EXPECT_TRUE(lose_called);
}

TEST(Widget, focusFunctionsNotCalledIfNotSet) {
    // Given
    TestWidget base;
    base.gainFocus = 0;
    base.loseFocus = 0;

    // When
    ASSERT_NO_THROW(base.focus(true));
    ASSERT_NO_THROW(base.focus(false));
}
