#include "collection_widget.h"
#include "curses.mock.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class RenderWidget : public Widget {
public:
    RenderWidget(const std::string& name) : Widget("") {
    }
    MOCK_METHOD1(render, void(const RenderContext&));
};

class TestWidget : public SwearJar::Widget {
public:
    TestWidget(const std::string& name) : Widget(name) {
        canTakeFocus(true);
    }
    void canTakeFocus(bool focus) {
        Widget::canTakeFocus(focus);
    }
    bool focus() {
        return Widget::focus();
    }
};

class TestCollectionWidget : public CollectionWidget {
public:
    TestCollectionWidget(const std::string& name) : CollectionWidget("") {
    }
    void canTakeFocus(bool focus) {
        Widget::canTakeFocus(focus);
    }
};

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
    base.createWidget<Widget>("");

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
    base.createWidget<TestWidget>("");

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
    KeyEvent e;
    e.key = 'X';

    // When
    bool retval = base.handleKeyPress(e);

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsFalseIfNoChildrenHasFocus) {
    // Given
    TestCollectionWidget base("");
    base.createWidget<Widget>("");
    KeyEvent e;
    e.key = 'X';

    // When
    bool retval = base.handleKeyPress(e);

    // Then
    EXPECT_FALSE(retval);
}

TEST(CollectionWidget, handleKeysReturnsTrueIfChildSelectedHasHandled) {
    class KeyPressWidget : public TestWidget {
    public:
        KeyPressWidget(const std::string& name) : TestWidget(name) {
        }
        bool handleKeyPress(const KeyEvent&) override {
            return true;
        }
    };

    // Given
    TestCollectionWidget base("");
    base.createWidget<KeyPressWidget>("");
    ASSERT_TRUE(base.moveFocusForward());
    KeyEvent e;
    e.key = 'X';

    // When
    bool retval = base.handleKeyPress(e);

    // Then
    EXPECT_TRUE(retval);
}

TEST(CollectionWidget, requiredWidthReturnsTotalRequiredWidthOfChildren) {
    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<Widget>("");
    c1.minWidth(5);
    auto& c2 = base.createWidget<Widget>("");
    c2.minWidth(7);

    // When
    unsigned int width = base.requiredWidth();

    // Then
    EXPECT_EQ(12, width);
}

TEST(CollectionWidget, requiredHeightReturnsTotalRequiredHeightOfChildren) {
    // Given
    TestCollectionWidget base("");
    auto& c1 = base.createWidget<Widget>("");
    c1.minHeight(5);
    auto& c2 = base.createWidget<Widget>("");
    c2.minHeight(7);

    // When
    unsigned int height = base.requiredHeight();

    // Then
    EXPECT_EQ(12, height);
}

TEST(CollectionWidget, creatingWidgetSetsSameBackgroundColor) {
    // Given
    CollectionWidget base("base");
    base.bgColor(12);

    // When
    auto& c1 = base.createWidget<RenderWidget>("");

    // Then
    EXPECT_EQ(base.bgColor(), c1.bgColor());
}

TEST(CollectionWidget, handleMouseEventReturnsFalseIfNoWidgets) {
    // Given
    CollectionWidget base("base");

    // When
    bool handled = base.handleMouseClick(MouseEvent());

    // Then
    EXPECT_FALSE(handled);
}

TEST(CollectionWidget, handleMouseEventReturnsTrueIfCoordInWidget) {
    // Given
    CollectionWidget base("base");
    auto& c1 = base.createWidget<RenderWidget>("");
    c1.x(10);
    c1.y(10);
    c1.width(20);
    c1.height(20);

    // When
    MouseEvent event;
    event.x = 15;
    event.y = 15;
    bool handled = base.handleMouseClick(event);

    // Then
    EXPECT_TRUE(handled);
}

TEST(CollectionWidget, handleMouseEventReturnsFalseIfNoneMatch) {
    // Given
    CollectionWidget base("base");
    auto& c1 = base.createWidget<RenderWidget>("");
    c1.x(10);
    c1.y(10);
    c1.width(20);
    c1.height(20);

    // When
    MouseEvent event;
    event.x = 5;
    event.y = 5;
    bool handled = base.handleMouseClick(event);

    // Then
    EXPECT_FALSE(handled);
}

TEST(CollectionWidget, renderCallsRenderForEachWidget) {
    // Given
    CollectionWidget base("base");
    auto& c1 = base.createWidget<RenderWidget>("");
    auto& c2 = base.createWidget<RenderWidget>("");

    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(c1, render(_));
    EXPECT_CALL(c2, render(_));

    // When
    base.render(*context);
}

TEST(CollectionWidget, renderSetsAndClearsOffsetsForEachWidget) {
    // Given
    CollectionWidget base("base");
    auto& c1 = base.createWidget<NiceMock<RenderWidget>>("");
    c1.x(10);
    c1.y(10);

    auto& c2 = base.createWidget<NiceMock<RenderWidget>>("");
    c2.x(20);
    c2.y(20);

    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, addOffsets(Eq(c1.x()), Eq(c1.y())));
    EXPECT_CALL(*context, addOffsets(Eq(c2.x()), Eq(c2.y())));
    EXPECT_CALL(*context, clearOffsets(_, _)).Times(2);

    // When
    base.render(*context);
}

TEST(CollectionWidget, renderSetsFocusIfSetOnWidget) {
    // Given
    CollectionWidget base("base");
    auto& c1 = base.createWidget<TestWidget>("");
    c1.moveFocusForward();

    base.createWidget<TestWidget>("");

    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, reverse(Eq(true)));
    EXPECT_CALL(*context, reverse(Eq(false))).Times(3);

    // When
    base.render(*context);
}

TEST(CollectionWidget, getWidgetReturnsWidgetIfFound) {
    // Given
    CollectionWidget base("base");
    auto& foo = base.createWidget<TestWidget>("foo");

    // When
    auto* found = base.getWidget<TestWidget>("foo");

    // Then
    ASSERT_NE(nullptr, found);
    EXPECT_EQ(foo.name(), found->name());
}

TEST(CollectionWidget, getWidgetReturnsNullptrIfNotFound) {
    // Given
    CollectionWidget base("base");
    base.createWidget<TestWidget>("foo");

    // When
    auto* found = base.getWidget<TestWidget>("bar");

    // Then
    EXPECT_EQ(nullptr, found);
}

TEST(CollectionWidget, getWidgetReturnsWidgetIfNested) {
    // Given
    CollectionWidget base("base");
    auto& nested = base.createWidget<CollectionWidget>("nested");
    nested.createWidget<TestWidget>("foo");

    // When
    auto* found = base.getWidget<TestWidget>("foo");

    // Then
    EXPECT_NE(nullptr, found);
}