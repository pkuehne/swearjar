#include "curses.mock.h"
#include "panel.h"
#include "widget.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;

class MockWidget : public Widget {
public:
    MockWidget() : Widget("") {}
    MOCK_METHOD1(refresh, void(const RenderContext&));
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

TEST(Panel, refreshDirtyWidgetsOnlyRefreshesDirtyWidgets) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Panel p(0, curses, 1, 1);

    auto w1 = std::make_shared<MockWidget>();
    w1->dirty(true);
    auto w2 = std::make_shared<MockWidget>();
    w2->dirty(false);

    p.addWidget(w1);
    p.addWidget(w2);

    // Then
    EXPECT_CALL(*w1, refresh(::testing::_)).Times(1);
    EXPECT_CALL(*w2, refresh(::testing::_)).Times(0);

    // When
    p.refreshDirtyWidgets();

    // Then
    EXPECT_FALSE(w1->dirty());
}

TEST(Panel, refreshDirtyWidgetsSetsWidgetClean) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    Panel p(0, curses, 1, 1);

    auto w1 = std::make_shared<::testing::NiceMock<MockWidget>>();
    w1->dirty(true);

    p.addWidget(w1);

    // When
    p.refreshDirtyWidgets();

    // Then
    EXPECT_FALSE(w1->dirty());
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
