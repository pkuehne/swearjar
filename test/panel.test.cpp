#include "curses.mock.h"
#include "panel.h"
#include "widget.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;

class MockWidget : public Widget {
public:
    MockWidget() : Widget("") {}
    MOCK_METHOD1(render, void(const RenderContextP&));
};

TEST(Panel, addWidgetIncreasesWidgetCount) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    SwearJar::Panel p(0, curses, 1, 1);

    // When
    p.addWidget(std::make_shared<SwearJar::Widget>(""));

    // Then
    EXPECT_EQ(p.widgets().size(), 1);
}

TEST(Widget, createWidgetAddsOneAndReturns) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    SwearJar::Panel p(0, curses, 1, 1);
    auto newWidget = p.createWidget<Widget>("", 0, 0);

    // Then
    EXPECT_TRUE(newWidget);
    EXPECT_FALSE(p.widgets().empty());
}

TEST(Widget, createWidgetWithoutCoordinatesSetsThemToZero) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    SwearJar::Panel p(0, curses, 1, 1);
    auto newWidget = p.createWidget<Widget>("test");

    // Then
    EXPECT_TRUE(newWidget);
    EXPECT_EQ("test", newWidget->name());
    EXPECT_EQ(0, newWidget->x());
    EXPECT_EQ(0, newWidget->y());
}

TEST(Panel, baseWidgetInitializedToHeightAndWidth) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Panel p(0, curses, 10, 20);

    // When
    auto base = p.baseWidget();

    // Then
    EXPECT_EQ(base->width(), p.width());
    EXPECT_EQ(base->height(), p.height());
}
