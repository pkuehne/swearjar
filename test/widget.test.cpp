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

TEST(Widget, initializesDirtyToTrue) {

    Widget w("");
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingXMarksDirty) {
    // Given
    Widget w("");
    w.dirty(false);

    // When
    w.x(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingYMarksDirty) {
    // Given
    Widget w("");
    w.dirty(false);

    // When
    w.y(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingWidthMarksDirty) {
    // Given
    Widget w("");
    w.dirty(false);

    // When
    w.width(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingHeightMarksDirty) {
    // Given
    Widget w("");
    w.dirty(false);

    // When
    w.height(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, prevDimensionIsSetWhenDirtied) {
    // Given
    Widget w("");
    w.height(20);
    w.width(30);
    w.x(2);
    w.y(5);
    w.dirty(false);

    // When
    w.x(4);

    // Then
    Dimension d = w.prevDimension();
    EXPECT_EQ(20, d.height);
    EXPECT_EQ(30, d.width);
    EXPECT_EQ(2, d.x);
    EXPECT_EQ(5, d.y);
}

TEST(Widget, clearPrevDimensionSetsAllToZero) {
    // Given
    TestWidget w;
    w.height(20);
    w.width(30);
    w.x(2);
    w.y(5);
    w.dirty(false);
    w.x(4);

    Dimension d1 = w.prevDimension();
    ASSERT_NE(0, d1.height);
    ASSERT_NE(0, d1.width);
    ASSERT_NE(0, d1.x);
    ASSERT_NE(0, d1.y);

    // When
    w.clearPrevDimension();

    Dimension d2 = w.prevDimension();
    ASSERT_EQ(0, d2.height);
    ASSERT_EQ(0, d2.width);
    ASSERT_EQ(0, d2.x);
    ASSERT_EQ(0, d2.y);
}

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
