#include "curses.mock.h"
#include "frame.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class FrameWidget : public Test {
public:
    void SetUp() {
        curses = std::make_shared<::testing::NiceMock<MockCurses>>();
        context = std::make_unique<MockRenderContext>(*curses);
    }

protected:
    std::shared_ptr<MockCurses> curses;
    std::unique_ptr<MockRenderContext> context;
    Frame frame{"frmFrame"};
};

TEST_F(FrameWidget, rendersTitleAndBorder) {
    // Given
    std::string title("test title");
    frame.title(title);
    EXPECT_CALL(*context, drawText(_, _, Eq(title), _, _));
    EXPECT_CALL(*context, drawBorder(_, _, _, _, _, _));

    // When
    frame.render(*context);

    // Then
}

TEST_F(FrameWidget, minWidthIsAtLeastTitleWidth) {
    // Given

    // When
    frame.title("Foo bar baz");

    // Then
    EXPECT_GE(frame.minWidth(), frame.title().size());
}

TEST_F(FrameWidget, minWidthIsAtLeastChildWidgetWidth) {
    // Given
    auto& w = frame.createWidget<Widget>("testWidget");
    w.minWidth(20);

    // When
    frame.title("Foo");

    // Then
    EXPECT_GE(frame.minWidth(), w.minWidth());
}