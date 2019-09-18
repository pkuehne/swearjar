#include "curses.mock.h"
#include "widget.h"
#include "window.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;

class MockWidget : public Widget {
public:
    MockWidget() : Widget("") {}
    MOCK_METHOD1(render, void(const RenderContextP&));
};

TEST(Panel, baseWidgetInitializedToHeightAndWidth) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Panel p(0, curses, 10, 20);

    // When
    auto& base = p.baseWidget();

    // Then
    EXPECT_EQ(base.width(), p.width());
    EXPECT_EQ(base.height(), p.height());
}
