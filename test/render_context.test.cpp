#include "curses.mock.h"
#include "render_context.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(RenderContext, clearAreaWritesSpaces) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    unsigned int window = 1;
    RenderContext context(curses, window);
    context.width(80);
    context.height(25);

    // Then
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(' '))).Times(6);

    // When
    context.clearArea(0, 0, 2, 3, 0, 0);
}

TEST(RenderContext, drawTextOnlySetsColorOnce) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    unsigned int window = 1;
    RenderContext context(curses, window);
    context.width(80);
    context.height(25);

    // Then
    EXPECT_CALL(*curses, color_on(_)).Times(1);
    EXPECT_CALL(*curses, color_off(_)).Times(1);

    // When
    context.drawText(0, 0, "FooBar", 1, 1);
}
