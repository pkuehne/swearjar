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
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Window w(curses, 0, 0, 10, 20);

    // When
    auto& base = w.baseWidget();

    // Then
    EXPECT_EQ(base.width(), w.width());
    EXPECT_EQ(base.height(), w.height());
}
