#include "curses.mock.h"
#include "widget.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;

class MockWidget : public Widget {
public:
    MockWidget() : Widget("") {}
    MOCK_METHOD1(render, void(const RenderContext&));
};

TEST(Window, baseWidgetInitializedToHeightAndWidth) {
    // Given
    unsigned int width = 10;
    unsigned int height = 20;
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);
    Window w(screen, 0, 0, width, height);

    // When
    auto& base = w.baseWidget();

    // Then
    EXPECT_EQ(base.width(), width);
    EXPECT_EQ(base.height(), height);
}

TEST(Window, initSizingInformation) {
    // Given
    unsigned int x = 10;
    unsigned int y = 20;
    unsigned int width = 30;
    unsigned int height = 40;
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Screen screen(curses);

    // When
    Window w(screen, x, y, width, height);

    // Then
    EXPECT_EQ(w.x(), x);
    EXPECT_EQ(w.y(), y);
    EXPECT_EQ(w.width(), width);
    EXPECT_EQ(w.height(), height);
}

class Window_contains : public ::testing::Test {

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

TEST_F(Window_contains, insideXinsideY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(20, 30);

    // Then
    EXPECT_TRUE(inside);
}

TEST_F(Window_contains, outsideXoutsideY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(5, 80);

    // Then
    EXPECT_FALSE(inside);
}

TEST_F(Window_contains, equalXequalY) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(10, 40);

    // Then
    EXPECT_TRUE(inside);
}

TEST_F(Window_contains, equalWidthEqualHeight) {
    // Given
    Screen screen(curses);
    Window w(screen, x, y, width, height);

    // When
    bool inside = w.contains(40, 60);

    // Then
    EXPECT_TRUE(inside);
}
