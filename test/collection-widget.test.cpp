#include "collection_widget.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

using namespace SwearJar;
using namespace ::testing;

class RefreshableWidget : public Widget {
public:
    RefreshableWidget(const std::string& name) : Widget("") {}
    MOCK_METHOD1(render, void(const RenderContext&));
};

class TestWidget : public SwearJar::Widget {
public:
    TestWidget(const std::string& name) : Widget("") { canTakeFocus(true); }
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
    bool focus() { return Widget::focus(); }
};

class TestCollectionWidget : public CollectionWidget {
public:
    TestCollectionWidget(const std::string& name) : CollectionWidget("") {}
    void canTakeFocus(bool focus) { Widget::canTakeFocus(focus); }
};

TEST(CollectionWidget, dirtyIsTrueIfDirtyChildWidgetExists) {
    // Given
    TestCollectionWidget base("");

    // When
    Widget& c = base.createWidget<Widget>("");

    // Then
    EXPECT_TRUE(base.dirty());
}

TEST(CollectionWidget, dirtyIsFalseIfNoDirtyChildWidgetExists) {
    // Given
    TestCollectionWidget base("");
    Widget& c = base.createWidget<Widget>("");
    Widget& d = base.createWidget<Widget>("");

    // When
    c.dirty(false);
    d.dirty(false);

    // Then
    EXPECT_FALSE(base.dirty());
}

TEST(CollectionWidget, initializesWithNoChildren) {
    // Given
    TestCollectionWidget base("");

    // Then
    EXPECT_TRUE(base.children().empty());
}

TEST(CollectionWidget, addingWidgetIncreasesChildCount) {
    // Given
    TestCollectionWidget base("");

    // When
    Widget& c = base.createWidget<Widget>("");

    // Then
    EXPECT_FALSE(base.children().empty());
}

TEST(CollectionWidget, moveFocusSetsFirstWidgetByDefault) {
    // Given
    TestCollectionWidget base("");
    Widget& c1 = base.createWidget<TestWidget>("");
    Widget& c2 = base.createWidget<TestWidget>("");

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c1.focus());
    EXPECT_FALSE(c2.focus());
}

TEST(CollectionWidget, moveFocusAdvancesSecondTime) {
    // Given
    TestCollectionWidget base("");
    Widget& c1 = base.createWidget<TestWidget>("");
    Widget& c2 = base.createWidget<TestWidget>("");

    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(c1.focus());
    EXPECT_TRUE(c2.focus());
}

TEST(CollectionWidget, moveFocusReturnsFalseWhenNoMoreWidgets) {
    // Given
    TestCollectionWidget base("");
    Widget& c1 = base.createWidget<TestWidget>("");
    Widget& c2 = base.createWidget<TestWidget>("");

    base.moveFocusForward();
    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(c1.focus());
    EXPECT_FALSE(c2.focus());
}

TEST(CollectionWidget, moveFocusSkipsChildrenThatCantTakeFocus) {
    // Given
    TestCollectionWidget base("");
    Widget& c1 = base.createWidget<TestWidget>("");
    TestWidget& c2 = base.createWidget<TestWidget>("");
    c2.canTakeFocus(false);
    Widget& c3 = base.createWidget<TestWidget>("");

    base.moveFocusForward();

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(c1.focus());
    EXPECT_FALSE(c2.focus());
    EXPECT_TRUE(c3.focus());
}

TEST(CollectionWidget, moveFocusReturnsFalseEvenIfItCouldTakeFocus) {
    // Given
    TestCollectionWidget base("");
    base.canTakeFocus(true);

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_FALSE(retval);
    EXPECT_FALSE(base.focus());
}

TEST(CollectionWidget, moveFocusDoesNotFocusOnParentEvenIfItCanTakeFocus) {
    // Given
    TestCollectionWidget base("");
    base.canTakeFocus(true);

    Widget& c1 = base.createWidget<TestWidget>("");

    // When
    bool retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_FALSE(base.focus());
    EXPECT_TRUE(c1.focus());
}

TEST(CollectionWidget, moveFocusWillCallSameChildAgainTillItReturnsFalse) {
    // Given
    TestCollectionWidget base("");
    bool retval = false;
    auto& c1 = base.createWidget<TestCollectionWidget>("");
    auto& c11 = c1.createWidget<TestWidget>("");
    auto& c12 = c1.createWidget<TestWidget>("");
    auto& c2 = base.createWidget<TestWidget>("");

    // When
    retval = base.moveFocusForward();

    // Then
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c11.focus());

    retval = base.moveFocusForward();
    EXPECT_TRUE(retval);
    EXPECT_TRUE(c12.focus());
}

TEST(CollectionWidget, handleKeysReturnsFalseIfNoChildrenByDefault) {
    // Given
    TestCollectionWidget base("");

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsFalseIfNoChildrenHasFocus) {
    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<Widget>("");

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsTrueIfChildSelectedHasHandled) {
    class KeyPressWidget : public TestWidget {
    public:
        KeyPressWidget(const std::string& name) : TestWidget(name) {}
        bool handleKeyPress(int ch) { return true; }
    };

    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<KeyPressWidget>("");
    ASSERT_TRUE(base.moveFocusForward());

    // When
    bool retval = base.handleKeyPress('X');

    // Then
    EXPECT_TRUE(retval);
}

TEST(CollectionWidget, minWidthReturnsTotalMinWidthOfChildren) {
    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(5);
    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(7);

    // When
    unsigned int width = base.minWidth();

    // Then
    EXPECT_EQ(12, width);
}

TEST(CollectionWidget, minHeightReturnsTotalMinHeightOfChildren) {
    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<Widget>("");
    c1.minHeight(5);
    auto& c2 = base.createWidget<Widget>("");
    c2.minHeight(7);

    // When
    unsigned int height = base.minHeight();

    // Then
    EXPECT_EQ(12, height);
}

TEST(CollectionWidget, renderOnlyRendersDirtyWidgets) {
    // Given
    auto context = std::make_unique<::testing::NiceMock<MockRenderContext>>();

    CollectionWidget base("base");

    auto& c1 = base.createWidget<RefreshableWidget>("");
    c1.dirty(false);
    EXPECT_CALL(c1, render(_)).Times(0);

    auto& c2 = base.createWidget<RefreshableWidget>("");
    c2.dirty(true);
    EXPECT_CALL(c2, render(_)).Times(1);

    // When
    base.render(*context);
}

TEST(CollectionWidget, creatingWidgetSetsSameBackgroundColor) {
    // Given
    CollectionWidget base("base");
    base.bgColor(12);

    // When
    auto& c1 = base.createWidget<RefreshableWidget>("");

    // Then
    EXPECT_EQ(base.bgColor(), c1.bgColor());
}
