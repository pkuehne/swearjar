#include "panel.h"
#include "widget.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace SwearJar {
class MockWidget : public Widget {
public:
    MOCK_METHOD0(refresh, void());
};

class MockCurses : public CursesInterface {
public:
    MOCK_METHOD0(getchar, int());
    MOCK_METHOD4(newwin, unsigned int(int, int, int, int));
    MOCK_METHOD0(currentWindow, unsigned int());
    MOCK_METHOD0(has_colors, bool());
    MOCK_METHOD2(get_color, short(short, short));
};

} // namespace SwearJar

TEST(Panel, addWidgetIncreasesWidgetCount) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<MockCurses>();
    Panel p(0, curses, 1, 1);

    // When
    p.addWidget(std::make_shared<Widget>());

    // Then
    EXPECT_EQ(p.widgets().size(), 1);
}

TEST(Panel, refreshDirtyWidgetsOnlyRefreshesDirtyWidgets) {
    using namespace SwearJar;

    // Given
    auto curses = std::make_shared<MockCurses>();
    Panel p(0, curses, 1, 1);
    ;

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
