#include "curses.mock.h"
#include "screen.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class ScreenClass : public Test {
public:
    void SetUp() {
    }

protected:
    std::shared_ptr<MockCurses> curses{
        std::make_shared<NiceMock<MockCurses>>()};
    Screen screen{curses};
};

TEST_F(ScreenClass, popWindowDoesNothingIfThereAreNoWindows) {
    // Given
    ASSERT_EQ(0, screen.windows().size());

    // When
    EXPECT_NO_THROW(screen.popWindow());
}

TEST_F(ScreenClass, popWindowRemovesNewestWindow) {
    // Given
    ASSERT_EQ(0, screen.windows().size());
    screen.createWindow<Window>();
    screen.createWindow<Window>();

    // When
    screen.popWindow();

    //
    EXPECT_EQ(1, screen.windows().size());
}

TEST_F(ScreenClass, destructorUndoesCursesMode) {
    // Given
    auto mock = std::make_shared<NiceMock<MockCurses>>();
    EXPECT_CALL(*mock, endwin());
    {
        Screen s(mock);
        // When
    }
}
