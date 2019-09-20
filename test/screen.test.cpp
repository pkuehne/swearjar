#include "curses.mock.h"
#include "screen.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(Screen, createWindowWithouthParamsMakesScreenSize) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);
    int width = 123;
    int height = 456;

    EXPECT_CALL(*curses, newwin(Eq(height), Eq(width), _, _));
    EXPECT_CALL(*curses, get_screen_size(_, _))
        .WillOnce(DoAll(SetArgReferee<0>(height), SetArgReferee<1>(width)));

    // When
    auto& window = screen.createWindow<Window>();

    // Then
    EXPECT_EQ(window.baseWidget().width(), width);
    EXPECT_EQ(window.baseWidget().height(), height);
    EXPECT_EQ(window.baseWidget().x(), 0);
    EXPECT_EQ(window.baseWidget().y(), 0);
}

TEST(Screen, createWindowWithWidthAndHeightStillSetsXYToZero) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);
    int width = 123;
    int height = 456;

    EXPECT_CALL(*curses, get_screen_size(_, _))
        .WillOnce(DoAll(SetArgReferee<0>(height), SetArgReferee<1>(width)));

    // When
    auto& window = screen.createWindow<Window>(50, 50);

    // Then
    EXPECT_EQ(window.baseWidget().x(), 0);
    EXPECT_EQ(window.baseWidget().y(), 0);
}

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
