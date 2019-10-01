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

        EXPECT_CALL(*context, reverse(Eq(false))).Times(AnyNumber());
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

TEST_F(ListWidget, renderSetsFocusFlagIfHasFocus) {
    // Given
    EXPECT_CALL(*context, drawText(_, _, _, _, _)).Times(3);
    EXPECT_CALL(*context, reverse(Eq(true))).Times(1);

    list.moveFocusForward();

    // When
    list.render(*context);

    // Then
    EXPECT_TRUE(list.focus());
}

TEST_F(ListWidget, settingItemOffsetDoesNotGoBeyondItems) {
    // When
    list.itemOffset(10);

    // Then
    EXPECT_EQ(list.itemOffset(), 2);
}

TEST_F(ListWidget, pageDownIncreasesItemOffset) {
    // Given
    KeyEvent event;
    event.key = KEY_PGDOWN;

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 1);
}

TEST_F(ListWidget, pageUpDecreasesItemOffset) {
    // Given
    KeyEvent event;
    event.key = KEY_PGUP;

    list.itemOffset(2);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 1);
}

TEST_F(ListWidget, pageUpDoesNotGoBeyondZero) {
    // Given
    KeyEvent event;
    event.key = KEY_PGUP;

    list.itemOffset(0);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.itemOffset(), 0);
}

TEST_F(ListWidget, selectedItemClampsToMax) {
    // Given

    // When
    list.selectedItem(10);

    // Then
    EXPECT_EQ(list.selectedItem(), 4);
}

TEST_F(ListWidget, selectedItemSetToArgument) {
    // Given

    // When
    list.selectedItem(3);

    // Then
    EXPECT_EQ(list.selectedItem(), 3);
}

TEST_F(ListWidget, selectedItemSetToZeroIfNoItems) {
    // Given

    // When
    emptyList.selectedItem(3);

    // Then
    EXPECT_EQ(emptyList.selectedItem(), 0);
}

TEST_F(ListWidget, upArrowDecreasesSelectedItem) {
    // Given
    KeyEvent event;
    event.key = KEY_UP;

    list.selectedItem(2);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.selectedItem(), 1);
}

TEST_F(ListWidget, upArrowDoesntDecreaseBeyondZero) {
    // Given
    KeyEvent event;
    event.key = KEY_UP;

    list.selectedItem(0);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.selectedItem(), 0);
}

TEST_F(ListWidget, downArrowIncreasesSelectedItem) {
    // Given
    KeyEvent event;
    event.key = KEY_DOWN;

    list.selectedItem(2);

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_EQ(list.selectedItem(), 3);
}

TEST_F(ListWidget, settingSelectedItemSmallerThanOffsetAdjustsOffset) {
    // Given
    list.selectedItem(2);
    list.itemOffset(2);
    ASSERT_EQ(list.selectedItem(), 2);
    ASSERT_EQ(list.itemOffset(), 2);

    // When
    list.selectedItem(1);

    // Then
    ASSERT_EQ(list.selectedItem(), 1);
    EXPECT_EQ(list.itemOffset(), 1);
}

TEST_F(ListWidget, settingSelectedItemLargerThanOffsetPlusWidthAdjustsOffset) {
    // Given
    list.selectedItem(1);
    list.itemOffset(1);
    ASSERT_EQ(list.selectedItem(), 1);
    ASSERT_EQ(list.itemOffset(), 1);

    // When
    list.selectedItem(4);

    // Then
    ASSERT_EQ(list.selectedItem(), 4);
    EXPECT_EQ(list.itemOffset(), 2);
}

TEST_F(ListWidget, settingItemOffsetSmallerThanSelectedItemAdjustsIt) {
    // Given
    list.selectedItem(4);
    list.itemOffset(2);
    ASSERT_EQ(list.selectedItem(), 4);
    ASSERT_EQ(list.itemOffset(), 2);

    // When
    list.itemOffset(0);

    // Then
    EXPECT_EQ(list.itemOffset(), 0);
    EXPECT_EQ(list.selectedItem(), 2);
}

TEST_F(ListWidget, settingItemOffsetBeyondSelectedItemAdjustsSelectedItem) {
    // Given
    list.selectedItem(0);
    list.itemOffset(0);
    ASSERT_EQ(list.selectedItem(), 0);
    ASSERT_EQ(list.itemOffset(), 0);

    // When
    list.itemOffset(2);

    // Then
    EXPECT_EQ(list.itemOffset(), 2);
    EXPECT_EQ(list.selectedItem(), 2);
}

TEST_F(ListWidget, settingSelectedItemTriggersCallback) {
    // Given
    bool selected = false;
    list.onSelected = [&selected](List&) { selected = true; };

    // When
    list.selectedItem(2);

    // Then
    EXPECT_TRUE(selected);
}

TEST_F(ListWidget, onSelectedOnlyTriggeredIfSelectionChanges) {
    // Given
    list.selectedItem(2);
    bool selected = false;
    list.onSelected = [&selected](List&) { selected = true; };

    // When
    list.selectedItem(2);

    // Then
    EXPECT_FALSE(selected);
}

TEST_F(ListWidget, onSelectedNotTriggeredIfNotSet) {
    // Given
    list.onSelected = nullptr;

    // When
    EXPECT_NO_THROW(list.selectedItem(2));
}

TEST_F(ListWidget, pressingEnterTriggersCallback) {
    // Given
    bool triggered = false;
    list.onTriggered = [&triggered](List&) { triggered = true; };

    KeyEvent event;
    event.key = 10;

    // When
    list.handleKeyPress(event);

    // Then
    EXPECT_TRUE(triggered);
}

TEST_F(ListWidget, pressingEnterTriggersCallbackIfSet) {
    // Given
    list.onTriggered = nullptr;

    KeyEvent event;
    event.key = 10;

    // When
    EXPECT_NO_THROW(list.handleKeyPress(event));
}
