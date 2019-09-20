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
