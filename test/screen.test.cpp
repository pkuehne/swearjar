#include "curses.mock.h"
#include "screen.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(Screen, popWindowDoesNothingIfThereAreNoWindows) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);

    ASSERT_EQ(0, screen.windows().size());

    // When
    EXPECT_NO_THROW(screen.popWindow());
}

TEST(Screen, popWindowRemovesNewestWindow) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);

    ASSERT_EQ(0, screen.windows().size());
    screen.createWindow<Window>();
    screen.createWindow<Window>();

    // When
    screen.popWindow();

    //
    EXPECT_EQ(1, screen.windows().size());
}
