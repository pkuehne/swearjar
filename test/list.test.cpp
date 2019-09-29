#include "curses.mock.h"
#include "list.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(List, addItemIncreasesItemList) {
    // Given
    List list("lstTest");

    // When
    list.addItem("item1");

    // Then
    EXPECT_EQ(1, list.items().size());
}

TEST(List, renderDoesNothingIfNoItems) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    auto context = std::make_unique<MockRenderContext>(*curses);
    List list("lstTest");

    EXPECT_CALL(*context, drawChar(_, _, _, _, _)).Times(0);
    EXPECT_CALL(*context, drawText(_, _, _, _, _)).Times(0);

    // When
    list.render(*context);
}

TEST(List, renderDrawsItems) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    auto context = std::make_unique<MockRenderContext>(*curses);
    List list("lstTest");
    std::string item1("Test 1");
    std::string item2("Test 2");
    list.addItem(item1);
    list.addItem(item2);

    EXPECT_CALL(*context, drawChar(_, _, _, _, _)).Times(0);
    EXPECT_CALL(*context, drawText(_, _, Eq(item1), _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(item2), _, _)).Times(1);

    // When
    list.render(*context);
}
