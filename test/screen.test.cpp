#include "curses.mock.h"
#include "screen.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST (ScreenClass, canCreateScreenWithNakedPointer) {
    // When
    Screen screen(new MockCurses());

    // Then
}

TEST(ScreenClass, popWindowDoesNothingIfThereAreNoWindows) {
    // Given
    Screen screen(std::make_shared<NiceMock<MockCurses>>());
    ASSERT_EQ(0, screen.windows().size());

    // When
    EXPECT_NO_THROW(screen.popWindow());
}

TEST(ScreenClass, popWindowRemovesNewestWindow) {
    // Given
    Screen screen(std::make_shared<NiceMock<MockCurses>>());
    ASSERT_EQ(0, screen.windows().size());
    screen.createWindow<Window>();
    screen.createWindow<Window>();

    // When
    screen.popWindow();

    //
    EXPECT_EQ(1, screen.windows().size());
}

TEST(ScreenClass, destructorUndoesCursesMode) {
    // Given
    auto mock = std::make_shared<NiceMock<MockCurses>>();
    EXPECT_CALL(*mock, endwin());
    {
        Screen s(mock);
        // When
    }
}
