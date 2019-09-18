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
    auto& window = screen.createWindow();

    // Then
    EXPECT_EQ(window.width(), width);
    EXPECT_EQ(window.height(), height);
}