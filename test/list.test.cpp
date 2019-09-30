#include "curses.mock.h"
#include "list.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class ListWidget : public Test {
public:
    void SetUp() {
        emptyList.height(3);

        list.height(3);
        list.addItem(item1);
        list.addItem(item2);
        list.addItem(item3);
        list.addItem(item4);
        list.addItem(item5);
    }

protected:
    std::shared_ptr<MockCurses> curses{
        std::make_shared<::testing::NiceMock<MockCurses>>()};
    std::unique_ptr<MockRenderContext> context{
        std::make_unique<MockRenderContext>(*curses)};

    List emptyList{"lstEmpty"};
    List list{"lstTest"};

    std::string item1{"Test 1"};
    std::string item2{"Test 2"};
    std::string item3{"Test 3"};
    std::string item4{"Test 4"};
    std::string item5{"Test 5"};
};

TEST_F(ListWidget, addItemIncreasesItemList) {
    // When
    emptyList.addItem(item1);

    // Then
    EXPECT_EQ(1, emptyList.items().size());
}

TEST_F(ListWidget, renderDoesNothingIfNoItems) {
    // Given
    EXPECT_CALL(*context, drawChar(_, _, _, _, _)).Times(0);
    EXPECT_CALL(*context, drawText(_, _, _, _, _)).Times(0);

    // When
    emptyList.render(*context);
}

TEST_F(ListWidget, renderDrawsItems) {
    // Given
    emptyList.addItem(item1);
    emptyList.addItem(item2);

    EXPECT_CALL(*context, drawText(_, _, Eq(item1), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item2), _, _)).Times(1);

    // When
    emptyList.render(*context);
}

TEST_F(ListWidget, renderDrawsOnlyItemsThatFitHeight) {
    // Given
    EXPECT_CALL(*context, drawText(_, _, Eq(item1), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item2), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item3), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item4), _, _)).Times(0);
    EXPECT_CALL(*context, drawText(_, _, Eq(item5), _, _)).Times(0);

    // When
    list.render(*context);
}

TEST_F(ListWidget, settingItemOffsetRendersNextItem) {
    // Given
    EXPECT_CALL(*context, drawText(_, _, Eq(item1), _, _)).Times(0);
    EXPECT_CALL(*context, drawText(_, _, Eq(item2), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item3), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item4), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item5), _, _)).Times(0);

    list.itemOffset(1);

    // When
    list.render(*context);
}

TEST_F(ListWidget, settingItemOffsetDoesNotGoBeyondItems) {
    // When
    list.itemOffset(10);

    // Then
    EXPECT_EQ(list.itemOffset(), 2);
}

TEST_F(ListWidget, downArrowIncreasesItemOffset) {
    // Given
    KeyEvent event;
    event.key = KEY_DOWN;

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 1);
}

TEST_F(ListWidget, upArrowDecreasesItemOffset) {
    // Given
    KeyEvent event;
    event.key = KEY_UP;

    list.itemOffset(2);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 1);
}

TEST_F(ListWidget, upArrowDoesNotGoBeyondZero) {
    // Given
    KeyEvent event;
    event.key = KEY_UP;

    list.itemOffset(0);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 0);
}
