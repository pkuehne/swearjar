#include "curses.mock.h"
#include "progressbar.h"
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

TEST(Progressbar, ZeroPercentRendersNothing) {
    // Given
    auto curses = std::make_shared<MockCurses>();
    unsigned int window = 1;
    RenderContextP context = std::make_unique<RenderContext>(curses, window);

    Progressbar bar("bar");
    bar.value(0);
    bar.maximum(100);

    // When
    bar.render(context);

    // Then
}

TEST(Progressbar, MaxValueRendersFullWidth) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    unsigned int window = 1;
    RenderContextP context = std::make_unique<RenderContext>(curses, window);
    context->width(20);
    context->height(5);

    EXPECT_CALL(*curses, mvaddch_(_, _, _)).Times(10);

    Progressbar bar("bar");
    bar.value(100);
    bar.maximum(100);
    bar.width(10);

    // When
    bar.render(context);
}

TEST(Progressbar, ValueAboveMaxRendersMax) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    unsigned int window = 1;
    RenderContextP context = std::make_unique<RenderContext>(curses, window);
    context->width(20);
    context->height(5);

    EXPECT_CALL(*curses, mvaddch_(_, _, _)).Times(10);

    Progressbar bar("bar");
    bar.value(200);
    bar.maximum(100);
    bar.width(10);

    // When
    bar.render(context);
}

TEST(Progressbar, FiftyPercentRendersHalf) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    unsigned int window = 1;
    RenderContextP context = std::make_unique<RenderContext>(curses, window);
    context->width(20);
    context->height(5);

    EXPECT_CALL(*curses, mvaddch_(_, _, _)).Times(5);

    Progressbar bar("bar");
    bar.value(50);
    bar.maximum(100);
    bar.width(10);

    // When
    bar.render(context);
}

TEST(Progressbar, incrementAddsOneToValue) {
    // Given
    Progressbar bar("bar");
    bar.value(2);
    bar.maximum(10);

    // When
    bar.increment();

    // Then
    EXPECT_EQ(bar.value(), 3);
}

TEST(Progressbar, decrementSubtractsOneFromValue) {
    // Given
    Progressbar bar("bar");
    bar.value(8);
    bar.maximum(10);

    // When
    bar.decrement();

    // Then
    EXPECT_EQ(bar.value(), 7);
}

TEST(Progressbar, decrementDoesNotGoBelowZero) {
    // Given
    Progressbar bar("bar");
    bar.value(0);
    bar.maximum(10);

    // When
    bar.decrement();

    // Then
    EXPECT_EQ(bar.value(), 0);
}

TEST(Progressbar, settingValueBeyondMaxSetsItToMax) {
    // Given
    Progressbar bar("bar");
    bar.value(0);
    bar.maximum(10);

    // When
    bar.value(20);

    // Then
    EXPECT_EQ(bar.value(), 10);
}
