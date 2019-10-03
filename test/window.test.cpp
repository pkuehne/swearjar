#include "curses.mock.h"
#include "widget.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;

class MockWidget : public Widget {
public:
    MockWidget() : Widget("") {
    }
    MOCK_METHOD1(render, void(const RenderContext&));
};

class WindowClass : public ::testing::Test {
    void SetUp() {
        curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    }

protected:
    unsigned int x = 10;
    unsigned int y = 20;
    unsigned int width = 30;
    unsigned int height = 40;
    std::shared_ptr<MockCurses> curses;
};

TEST_F(WindowClass, setWindowStyleFullScreenSetsTheStyleAndParams) {
    // Given
    Screen screen(curses);
    Window w(screen);

    // When
    w.setWindowStyleFullScreen();

    // Then
    EXPECT_EQ(w.style(), WindowStyle::FullScreen);
    EXPECT_EQ(0, w.params().fractionalWidth);
    EXPECT_EQ(0, w.params().fractionalHeight);
    EXPECT_EQ(0, w.params().fixedWidth);
    EXPECT_EQ(0, w.params().fixedHeight);
    EXPECT_EQ(0, w.params().fixedX);
    EXPECT_EQ(0, w.params().fixedY);
}

TEST_F(WindowClass, setWindowStyleFractionalSetsTheStyleAndParams) {
    // Given
    Screen screen(curses);
    Window w(screen);

    // When
    w.setWindowStyleFractional(50, 50);

    // Then
    EXPECT_EQ(w.style(), WindowStyle::Fractional);
    EXPECT_EQ(50, w.params().fractionalWidth);
    EXPECT_EQ(50, w.params().fractionalHeight);
}

TEST_F(WindowClass, setWindowStyleFixedSetsTheStyleAndParams) {
    // Given
    Screen screen(curses);
    Window w(screen);

    // When
    w.setWindowStyleFixed(x, y, width, height);

    // Then
    EXPECT_EQ(w.style(), WindowStyle::Fixed);
    EXPECT_EQ(width, w.params().fixedWidth);
    EXPECT_EQ(height, w.params().fixedHeight);
    EXPECT_EQ(x, w.params().fixedX);
    EXPECT_EQ(y, w.params().fixedY);
}

TEST_F(WindowClass, initSizingInformation) {
    // Given
    Screen screen(curses);

    // When
    Window w(screen, x, y, width, height);

    // Then
    EXPECT_EQ(w.x(), x);
    EXPECT_EQ(w.y(), y);
    EXPECT_EQ(w.width(), width);
    EXPECT_EQ(w.height(), height);
}

TEST_F(WindowClass, baseWidgetInitializedToHeightAndWidth) {
    // Given
    Screen screen(curses);
    Window w(screen, 0, 0, width, height);

    // When
    auto& base = w.baseWidget();

    // Then
    EXPECT_EQ(base.width(), width);
    EXPECT_EQ(base.height(), height);
}

TEST_F(WindowClass, insideXinsideY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(20, 30);

    // Then
    EXPECT_TRUE(inside);
}

TEST_F(WindowClass, outsideXoutsideY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(5, 80);

    // Then
    EXPECT_FALSE(inside);
}

TEST_F(WindowClass, equalXequalY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(10, 40);

    // Then
    EXPECT_TRUE(inside);
}

TEST_F(WindowClass, equalWidthEqualHeight) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(40, 60);

    // Then
    EXPECT_TRUE(inside);
}
