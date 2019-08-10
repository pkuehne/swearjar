#include "curses.mock.h"
#include "panel.h"
#include "widget.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace SwearJar {
class MockWidget : public Widget {
public:
    MOCK_METHOD0(refresh, void());
};

} // namespace SwearJar

TEST(Panel, addWidgetIncreasesWidgetCount) {
    // Given
    auto curses = std::make_shared<::testing::NiceMock<MockCurses>>();
    SwearJar::Panel p(0, curses, 1, 1);

    // When
    p.addWidget(std::make_shared<SwearJar::Widget>());

    // Then
    EXPECT_EQ(p.widgets().size(), 1);
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
    EXPECT_CALL(*w1, refresh()).Times(1);
    EXPECT_CALL(*w2, refresh()).Times(0);

    // When
    p.refreshDirtyWidgets();

    // Then
    EXPECT_FALSE(w1->dirty());
}

TEST(Panel, refreshDirtyWidgetsSetsWidgetClean) {
    using namespace SwearJar;

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
