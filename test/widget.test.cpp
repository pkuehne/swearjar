#include "curses.mock.h"
#include "widget.h"
#include <gtest/gtest.h>

class TestWidget : public SwearJar::Widget {
public:
    virtual ~TestWidget() {}
    virtual void clearWidget() { Widget::clearWidget(); }
    static void setCurses(const SwearJar::CIptr& mock) {
        Widget::curses = mock;
    }
};

TEST(Widget, initializesDirtyToTrue) {
    using namespace SwearJar;

    Widget w;
    EXPECT_TRUE(w.dirty());
}

TEST(Widget, clearWidgetSkipsIfDirty) {
    // Given
    TestWidget w;
    w.dirty(true);
    auto m = std::make_shared<MockCurses>();
    TestWidget::setCurses(m);

    // Then
    EXPECT_CALL(*m, mvaddch_(testing::_, testing::_, testing::_)).Times(0);

    // When
    w.clearWidget();
}

TEST(Widget, clearWidgetWritesSpaceInAllPlaces) {
    // Given
    TestWidget w;
    w.width(2);
    w.height(3);
    w.dirty(false);
    auto m = std::make_shared<MockCurses>();
    TestWidget::setCurses(m);

    // Then
    EXPECT_CALL(*m, mvaddch_(testing::_, testing::_, testing::_)).Times(6);

    // When
    w.clearWidget();
}