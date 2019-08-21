#include "curses.mock.h"
#include "widget.h"
#include <gtest/gtest.h>

class TestWidget : public SwearJar::Widget {
public:
    TestWidget() { canTakeFocus(true); }
    virtual ~TestWidget() {}
    void addWidget(SwearJar::WidgetP widget) { Widget::addWidget(widget); }
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
    void focus(bool focus) { Widget::focus(focus); }
    bool focus() { return Widget::focus(); }
};

TEST(Widget, initializesDirtyToTrue) {
    using namespace SwearJar;

    Widget w;
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingXMarksDirty) {
    // Given
    TestWidget w;
    w.dirty(false);

    // When
    w.x(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingYMarksDirty) {
    // Given
    TestWidget w;
    w.dirty(false);

    // When
    w.y(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingWidthMarksDirty) {
    // Given
    TestWidget w;
    w.dirty(false);

    // When
    w.width(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, settingHeightMarksDirty) {
    // Given
    TestWidget w;
    w.dirty(false);

    // When
    w.height(100);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, prevDimensionIsSetWhenDirtied) {
    using namespace SwearJar;

    // Given
    TestWidget w;
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
    using namespace SwearJar;

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

TEST(Widget, initializesWithNoChildren) {
    using namespace SwearJar;

    // Given
    TestWidget w;

    // Then
    EXPECT_TRUE(w.children().empty());
}

TEST(Widget, addingWidgetIncreasesChildCount) {
    using namespace SwearJar;

    // Given
    TestWidget w;
    WidgetP c = std::make_shared<Widget>();

    // When
    w.addWidget(c);

    // Then
    EXPECT_FALSE(w.children().empty());
}

TEST(Widget, moveFocusSetsFirstWidgetByDefault) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    WidgetP c1 = std::make_shared<TestWidget>();
    WidgetP c2 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c1->focus());
    EXPECT_FALSE(c2->focus());
}

TEST(Widget, moveFocusAdvancesSecondTime) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    WidgetP c1 = std::make_shared<TestWidget>();
    WidgetP c2 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);
    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(c1->focus());
    EXPECT_TRUE(c2->focus());
}

TEST(Widget, moveFocusReturnsFalseWhenNoMoreWidgets) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    WidgetP c1 = std::make_shared<TestWidget>();
    WidgetP c2 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);
    base.moveFocusForward();
    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(c1->focus());
    EXPECT_FALSE(c2->focus());
}

TEST(Widget, moveFocusSkipsChildrenThatCantTakeFocus) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    WidgetP c1 = std::make_shared<TestWidget>();
    auto c2 = std::make_shared<TestWidget>();
    c2->canTakeFocus(false);
    WidgetP c3 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);
    base.addWidget(c3);
    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(c1->focus());
    EXPECT_FALSE(c2->focus());
    EXPECT_TRUE(c3->focus());
}

TEST(Widget, moveFocusReturnsFalseWhenNoChildrenAndCantTakeFocus) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    base.canTakeFocus(false);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
}

TEST(Widget, moveFocusReturnsTrueWhenNoChildWidgetsButCanTakeFocus) {
    using namespace SwearJar;

    // Given
    TestWidget base;

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(base.focus());
}

TEST(Widget, moveFocusReturnsFalseIfAlreadyHasFocus) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    base.focus(true);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(base.focus());
}

TEST(Widget, moveFocusDoesNotFocusOnParentEvenIfItCanTakeFocus) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    base.canTakeFocus(true);

    WidgetP c1 = std::make_shared<TestWidget>();
    base.addWidget(c1);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(base.focus());
    EXPECT_TRUE(c1->focus());
}

TEST(Widget, moveFocusWillCallSameChildAgainTillItReturnsFalse) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    bool retval = false;
    auto c1 = std::make_shared<TestWidget>();
    auto c11 = std::make_shared<TestWidget>();
    auto c12 = std::make_shared<TestWidget>();
    auto c2 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);
    c1->addWidget(c11);
    c1->addWidget(c12);
    //base.moveFocusForward();

    // When
    retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c11->focus());

    retval = base.moveFocusForward();
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c12->focus());
}

TEST(Widget, gainFocusCalledWhenFocusSetToTrue) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&]() { gain_called = true; };
    base.loseFocus = [&]() { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(true));

    // Then
    EXPECT_TRUE(gain_called);
    EXPECT_FALSE(lose_called);
}

TEST(Widget, loseFocusFunctionCalledWhenFocusSetFalse) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    bool gain_called = false;
    bool lose_called = false;
    base.gainFocus = [&]() { gain_called = true; };
    base.loseFocus = [&]() { lose_called = true; };

    // When
    ASSERT_NO_THROW(base.focus(false));

    // Then
    EXPECT_FALSE(gain_called);
    EXPECT_TRUE(lose_called);
}

TEST(Widget, focusFunctionsNotCalledIfNotSet) {
    using namespace SwearJar;

    // Given
    TestWidget base;
    base.gainFocus = 0;
    base.loseFocus = 0;

    // When
    ASSERT_NO_THROW(base.focus(true));
    ASSERT_NO_THROW(base.focus(false));
}
