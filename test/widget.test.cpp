#include "widget.h"
#include <gtest/gtest.h>

using namespace SwearJar;

class TestWidget : public SwearJar::Widget {
public:
    TestWidget() : Widget("") {
        canTakeFocus(true);
    }
    virtual ~TestWidget() {
    }
    void canTakeFocus(bool focus) {
        Widget::canTakeFocus(focus);
    }
    void focus(bool focus) {
        Widget::focus(focus);
    }
    bool focus() {
        return Widget::focus();
    }
};

TEST(Widget, settingFgColor) {
    // Given
    Widget w("test");
    Color color = Color::Green;

    // When
    w.fgColor(color);

    // Then
    EXPECT_EQ(w.fgColor(), color);
}

TEST(Widget, settingBgColor) {
    // Given
    Widget w("test");
    Color color = Color::Green;

    // When
    w.bgColor(color);

    // Then
    EXPECT_EQ(w.bgColor(), color);
}

TEST(Widget, moveFocusReturnsFalse) {
    // Given
    TestWidget base;
    base.canTakeFocus(false);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
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
    base.focus(true);
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

TEST(Widget, loseFocusFunctionNotCalledWhenNotAlreadyHasFocus) {
    // Given
    TestWidget base;
    base.focus(false);
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&](Widget*) { gain_called = true; };
    base.loseFocus = [&](Widget*) { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(false));

    // Then
    EXPECT_FALSE(gain_called);
    EXPECT_FALSE(lose_called);
}

TEST(Widget, gainFocusFunctionNotCalledWhenNotAlreadyHasFocus) {
    // Given
    TestWidget base;
    base.focus(true);
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&](Widget*) { gain_called = true; };
    base.loseFocus = [&](Widget*) { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(true));

    // Then
    EXPECT_FALSE(gain_called);
    EXPECT_FALSE(lose_called);
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

TEST(Widget, defaultsToOneByOneSize) {
    // Given
    Widget w("");

    // Then
    EXPECT_EQ(1, w.height());
    EXPECT_EQ(1, w.width());
    EXPECT_EQ(1, w.requiredHeight());
    EXPECT_EQ(1, w.requiredWidth());
}

TEST(Widget, defaultsToZeroGrowthFactor) {
    // Given
    Widget w("");

    // Then
    EXPECT_EQ(0, w.growthFactor());
}

TEST(Widget, handleMouseClickDoesNothingByDefault) {
    // Given
    Widget w("");
    MouseEvent e;

    // Then
    EXPECT_TRUE(w.handleMouseClick(e));
}

TEST(Widget, handleKeyPressDoesNothingByDefault) {
    // Given
    Widget w("");
    KeyEvent e;

    // Then
    EXPECT_TRUE(w.handleKeyPress(e));
}