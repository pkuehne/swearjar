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
    std::wstring title(L"test title");
    frame.title(title);
    EXPECT_CALL(*context,
                drawText(_, _, TypedEq<const std::wstring&>(title), _, _));
    EXPECT_CALL(*context, drawBorder(_, _, _, _, _, _));

    // When
    frame.render(*context);

    // Then
}

TEST_F(FrameWidget, requiredWidthIsAtLeastTitleWidth) {
    // Given

    // When
    frame.title(L"Foo bar baz");

    // Then
    EXPECT_GE(frame.requiredWidth(), frame.title().size());
}

TEST_F(FrameWidget, titleDefaultsToLeftAligned) {
    // Given / When
    EXPECT_FALSE(frame.titleCentred());
}

TEST_F(FrameWidget, centredTitleRendersMidWidth) {
    // Given
    frame.width(20);
    std::wstring title(L"test");  // length 4 => xStart = (20-4)/2 = 8
    frame.title(title);
    frame.titleCentred(true);

    EXPECT_CALL(*context,
                drawText(8, _, TypedEq<const std::wstring&>(title), _, _));
    EXPECT_CALL(*context, drawBorder(_, _, _, _, _, _));

    // When
    frame.render(*context);
}

TEST_F(FrameWidget, uncentredTitleRendersAtPositionTwo) {
    // Given
    frame.width(20);
    std::wstring title(L"test");
    frame.title(title);
    frame.titleCentred(false);

    EXPECT_CALL(*context,
                drawText(2, _, TypedEq<const std::wstring&>(title), _, _));
    EXPECT_CALL(*context, drawBorder(_, _, _, _, _, _));

    // When
    frame.render(*context);
}

TEST_F(FrameWidget, requiredWidthIsAtLeastChildWidgetWidth) {
    // Given
    auto& w = frame.createWidget<Widget>("testWidget");
    w.minWidth(20);

    // When
    frame.title(L"Foo");

    // Then
    EXPECT_GE(frame.requiredWidth(), w.requiredWidth());
}
