#include "collection_widget.h"
#include <gtest/gtest.h>

using namespace SwearJar;

class TestWidget : public SwearJar::Widget {
public:
    TestWidget() : Widget("") { canTakeFocus(true); }
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
    bool focus() { return Widget::focus(); }
};

class TestCollectionWidget : public CollectionWidget {
public:
    TestCollectionWidget() : CollectionWidget("") {}
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
};

TEST(CollectionWidget, dirtyIsTrueIfDirtyChildWidgetExists) {
    // Given
    TestCollectionWidget w;
    WidgetP c = std::make_shared<Widget>("");

    // When
    w.addWidget(c);

    // Then
    EXPECT_TRUE(w.dirty());
}

TEST(CollectionWidget, dirtyIsFalseIfNoDirtyChildWidgetExists) {
    // Given
    TestCollectionWidget w;
    WidgetP c = std::make_shared<Widget>("");
    WidgetP d = std::make_shared<Widget>("");
    w.addWidget(c);
    w.addWidget(d);

    // When
    c->dirty(false);
    d->dirty(false);

    // Then
    EXPECT_FALSE(w.dirty());
}

TEST(CollectionWidget, initializesWithNoChildren) {
    // Given
    TestCollectionWidget w;

    // Then
    EXPECT_TRUE(w.children().empty());
}

TEST(CollectionWidget, addingWidgetIncreasesChildCount) {
    // Given
    TestCollectionWidget w;
    WidgetP c = std::make_shared<Widget>("");

    // When
    w.addWidget(c);

    // Then
    EXPECT_FALSE(w.children().empty());
}

TEST(CollectionWidget, moveFocusSetsFirstWidgetByDefault) {
    // Given
    TestCollectionWidget base;
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

TEST(CollectionWidget, moveFocusAdvancesSecondTime) {
    // Given
    TestCollectionWidget base;
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

TEST(CollectionWidget, moveFocusReturnsFalseWhenNoMoreWidgets) {
    // Given
    TestCollectionWidget base;
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

TEST(CollectionWidget, moveFocusSkipsChildrenThatCantTakeFocus) {
    // Given
    TestCollectionWidget base;
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

TEST(CollectionWidget, moveFocusReturnsFalseEvenIfItCouldTakeFocus) {
    // Given
    TestCollectionWidget base;
    base.canTakeFocus(true);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(base.focus());
}

TEST(CollectionWidget, moveFocusDoesNotFocusOnParentEvenIfItCanTakeFocus) {
    // Given
    TestCollectionWidget base;
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

TEST(CollectionWidget, moveFocusWillCallSameChildAgainTillItReturnsFalse) {
    // Given
    TestCollectionWidget base;
    bool retval = false;
    auto c1 = std::make_shared<TestCollectionWidget>();
    auto c11 = std::make_shared<TestWidget>();
    auto c12 = std::make_shared<TestWidget>();
    auto c2 = std::make_shared<TestWidget>();

    base.addWidget(c1);
    base.addWidget(c2);
    c1->addWidget(c11);
    c1->addWidget(c12);

    // When
    retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c11->focus());

    retval = base.moveFocusForward();
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c12->focus());
}

TEST(CollectionWidget, handleKeysReturnsFalseIfNoChildrenByDefault) {
    // Given
    TestCollectionWidget base;

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsFalseIfNoChildrenHasFocus) {
    // Given
    TestCollectionWidget base;
    auto c1 = std::make_shared<Widget>("");
    base.addWidget(c1);

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsTrueIfChildSelectedHasHandled) {
    class KeyPressWidget : public TestWidget {
    public:
        bool handleKeyPress(int ch) { return true; }
    };

    // Given
    TestCollectionWidget base;
    auto c1 = std::make_shared<KeyPressWidget>();
    base.addWidget(c1);
    ASSERT_TRUE(base.moveFocusForward());

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_TRUE(retval);
}

TEST(CollectionWidget, minWidthReturnsTotalMinWidthOfChildren) {
    // Given
    TestCollectionWidget base;
    auto c1 = std::make_shared<Widget>("");
    c1->minWidth(5);
    auto c2 = std::make_shared<Widget>("");
    c2->minWidth(7);
    base.addWidget(c1);
    base.addWidget(c2);

    // When
    unsigned int width = base.minWidth();

    // Then
    EXPECT_EQ(12, width);
}

TEST(CollectionWidget, minHeightReturnsTotalMinHeightOfChildren) {
    // Given
    TestCollectionWidget base;
    auto c1 = std::make_shared<Widget>("");
    c1->minHeight(5);
    auto c2 = std::make_shared<Widget>("");
    c2->minHeight(7);
    base.addWidget(c1);
    base.addWidget(c2);

    // When
    unsigned int height = base.minHeight();

    // Then
    EXPECT_EQ(12, height);
}

