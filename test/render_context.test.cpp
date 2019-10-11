#include "curses.mock.h"
#include "render_context.h"
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class RenderContextObject : public Test {
public:
    void SetUp() {
        ON_CALL(*curses, get_color(Eq(fg), Eq(bg)))
            .WillByDefault(Return(color));
        context.width(80);
        context.height(25);
        context.xOffset(xOffset);
        context.yOffset(yOffset);
    }

protected:
    std::shared_ptr<MockCurses> curses{
        std::make_shared<NiceMock<MockCurses>>()};
    unsigned int window = 1;
    RenderContext context{*curses, window};
    short fg = 1;
    short bg = 2;
    short color = 123;
    unsigned int x = 5;
    unsigned int y = 10;
    unsigned int xOffset = 2;
    unsigned int yOffset = 3;
};

TEST_F(RenderContextObject, clearsBackgroundWithGivenColours) {
    // Given
    short fg = 1;
    short bg = 2;
    short code = 123;
    EXPECT_CALL(*curses, get_color(Eq(fg), Eq(bg))).WillOnce(Return(code));
    EXPECT_CALL(*curses, wbkgd(Eq(code)));

    // When
    context.clearBackground(fg, bg);
}

TEST_F(RenderContextObject, drawsTextWithASCIIStringAndColor) {
    // Given
    std::string text("Foo");
    EXPECT_CALL(*curses, color_on(Eq(color)));
    EXPECT_CALL(*curses, color_off(Eq(color)));
    EXPECT_CALL(*curses, mvwprint(Eq(y + yOffset), Eq(x + xOffset), Eq(text)));

    // When
    context.drawText(x, y, text, fg, bg);
}

TEST_F(RenderContextObject, drawsTextWithWideStringAndColor) {
    // Given
    std::wstring text(L"Foo");
    EXPECT_CALL(*curses, color_on(Eq(color)));
    EXPECT_CALL(*curses, color_off(Eq(color)));
    EXPECT_CALL(*curses, mvwprintw(Eq(y + yOffset), Eq(x + xOffset), Eq(text)));

    // When
    context.drawText(x, y, text, fg, bg);
}

TEST_F(RenderContextObject, drawsAsciiCharIfInsideWidthAndHeight) {
    // Given
    char ch = 'F';
    EXPECT_CALL(*curses, mvaddch_(Eq(y + yOffset), Eq(x + xOffset), Eq(ch)));

    // When
    context.drawChar(x, y, ch);
}

TEST_F(RenderContextObject, wontdrawAsciiCharIfOutsideWidth) {
    // Given
    char ch = 'F';
    EXPECT_CALL(*curses, mvaddch_(_, _, _)).Times(0);

    // When
    context.drawChar(context.width() + 1, y, ch);
}

TEST_F(RenderContextObject, wontdrawAsciiCharIfOutsideHeight) {
    // Given
    char ch = 'F';
    EXPECT_CALL(*curses, mvaddch_(_, _, _)).Times(0);

    // When
    context.drawChar(x, context.height() + 1, ch);
}

TEST_F(RenderContextObject, drawsWideCharIfInsideWidthAndHeight) {
    // Given
    wchar_t ch = L'F';
    EXPECT_CALL(*curses, mvaddwch_(Eq(y + yOffset), Eq(x + xOffset), Eq(ch)));

    // When
    context.drawChar(x, y, ch);
}

TEST_F(RenderContextObject, wontdrawWideCharIfOutsideWidth) {
    // Given
    wchar_t ch = L'F';
    EXPECT_CALL(*curses, mvaddwch_(_, _, _)).Times(0);

    // When
    context.drawChar(context.width() + 1, y, ch);
}

TEST_F(RenderContextObject, wontdrawWideCharIfOutsideHeight) {
    // Given
    wchar_t ch = L'F';
    EXPECT_CALL(*curses, mvaddwch_(_, _, _)).Times(0);

    // When
    context.drawChar(x, context.height() + 1, ch);
}

TEST_F(RenderContextObject, drawsAsciiCharWithColor) {
    // Given
    char ch = 'F';
    EXPECT_CALL(*curses, color_on(Eq(color)));
    EXPECT_CALL(*curses, color_off(Eq(color)));
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(ch)));

    // When
    context.drawChar(x, y, ch, fg, bg);
}

TEST_F(RenderContextObject, drawsWideCharWithColor) {
    // Given
    wchar_t ch = L'F';
    EXPECT_CALL(*curses, color_on(Eq(color)));
    EXPECT_CALL(*curses, color_off(Eq(color)));
    EXPECT_CALL(*curses, mvaddwch_(_, _, Eq(ch)));

    // When
    context.drawChar(x, y, ch, fg, bg);
}

TEST_F(RenderContextObject, clearAreaWritesSpaces) {
    // Then
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(' '))).Times(6);

    // When
    context.clearArea(0, 0, 2, 3, 0, 0);
}

TEST_F(RenderContextObject, clearAreaWorksWithXYOffset) {
    // Then
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(' '))).Times(12);

    // When
    context.clearArea(1, 2, 3, 4, 0, 0);
}

TEST_F(RenderContextObject, clearAreaDoesNothingForZeroHeightWidth) {
    // Then
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(' '))).Times(0);

    // When
    context.clearArea(1, 2, 0, 0, 0, 0);
}

TEST_F(RenderContextObject, clearAreaOnlyClearsInsideOwnSize) {
    // Then
    EXPECT_CALL(*curses, mvaddch_(_, _, Eq(' '))).Times(36);

    // When
    context.clearArea(73, 17, 7, 7, 0, 0);
}

TEST_F(RenderContextObject, drawBorderDoesNotWorkBelowWidthOfThree) {
    // Given
    EXPECT_CALL(*curses, mvaddwch_(_, _, _)).Times(0);

    // When
    context.drawBorder(x, y, 1, 20, fg, bg);
}

TEST_F(RenderContextObject, drawBorderDoesNotWorkBelowHeightOfThree) {
    // Given
    EXPECT_CALL(*curses, mvaddwch_(_, _, _)).Times(0);

    // When
    context.drawBorder(x, y, 10, 2, fg, bg);
}

TEST_F(RenderContextObject, drawBorderSetsColorOnce) {
    // Given
    EXPECT_CALL(*curses, color_on(Eq(color)));
    EXPECT_CALL(*curses, color_off(Eq(color)));
    ON_CALL(*curses, mvaddwch_(_, _, _)).WillByDefault(Return());

    // When
    context.drawBorder(x, y, 10, 20, fg, bg);
}

TEST_F(RenderContextObject, beginRenderSetsCurrentWindow) {
    // Given
    EXPECT_CALL(*curses, currentWindow(Eq(window)));

    // When
    context.beginRender();
}

TEST_F(RenderContextObject, endRenderRefreshesWindow) {
    // Given
    EXPECT_CALL(*curses, wrefresh());

    // When
    context.endRender();
}

TEST_F(RenderContextObject, reverseWithTrueEnablesReverseMode) {
    // Given
    EXPECT_CALL(*curses, reverse_on());

    // When
    context.reverse(true);
}

TEST_F(RenderContextObject, reverseWithFalseDisablesReverseMode) {
    // Given
    EXPECT_CALL(*curses, reverse_off());

    // When
    context.reverse(false);
}

TEST_F(RenderContextObject, blinkWithTrueEnablesblinkMode) {
    // Given
    EXPECT_CALL(*curses, blink_on());

    // When
    context.blink(true);
}

TEST_F(RenderContextObject, blinkWithFalseDisablesblinkMode) {
    // Given
    EXPECT_CALL(*curses, blink_off());

    // When
    context.blink(false);
}
