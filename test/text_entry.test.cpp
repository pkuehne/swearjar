#include "curses.mock.h"
#include "render_context.mock.h"
#include "text_entry.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace SwearJar;
using namespace ::testing;

class TextEntryWidget : public Test {
public:
    void SetUp() {
        curses = std::make_shared<::testing::NiceMock<MockCurses>>();
        context = std::make_unique<MockRenderContext>(*curses);

        entry.width(10);
    }

protected:
    std::shared_ptr<MockCurses> curses;
    std::unique_ptr<MockRenderContext> context;

    TextEntry entry{"txtEntry"};

    KeyEvent kevent;
    MouseEvent mevent;
};

TEST_F(TextEntryWidget, canSetText) {
    // Given
    std::wstring testText(L"Test Test");

    // When
    entry.text(testText);

    // Then
    EXPECT_EQ(testText, entry.text());
}

TEST_F(TextEntryWidget, renderPlaceholderWhenNoText) {
    // Given
    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('_'), _, _))
        .Times(entry.width());
    EXPECT_CALL(*context,
                drawText(_, _, TypedEq<const std::wstring&>(L""), _, _));

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, renderTextWhenSetPlusPlaceholders) {
    // Given
    entry.text(L"TEST");
    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('_'), _, _)).Times(6);
    EXPECT_CALL(
        *context,
        drawText(_, _, TypedEq<const std::wstring&>(entry.text()), _, _));

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, pressingPrintableKeyAppendsToText) {
    // Given
    kevent.key = 'a';

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(entry.text(), L"a");
}

TEST_F(TextEntryWidget, pressingUnprintableKeyDoesNothing) {
    // Given
    kevent.key = '\t';

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_FALSE(handled);
    EXPECT_EQ(entry.text(), L"");
}

TEST_F(TextEntryWidget, pressingBackspaceKeyRemovesCharFromText) {
    // Given
    entry.text(L"Foo");
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(entry.text(), L"Fo");
}

TEST_F(TextEntryWidget, pressingBackspaceKeyDoesNothingOnEmptyString) {
    // Given
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(entry.text(), L"");
}

TEST_F(TextEntryWidget, renderBlinkIfHasFocus) {
    // Given
    entry.text(L"Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, blink(Eq(true)));
    EXPECT_CALL(*context, blink(Eq(false)));

    entry.moveFocusForward();

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, doesntRenderBlinkIfNoFocus) {
    // Given
    entry.text(L"Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, blink(Eq(true))).Times(0);
    EXPECT_CALL(*context, blink(Eq(false))).Times(0);

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, settingCursorBeyondTextClampsToTextLength) {
    // Given
    entry.text(L"Foo");

    // When
    entry.cursor(5);

    // Then
    EXPECT_EQ(3, entry.cursor());
}

TEST_F(TextEntryWidget, settingTextSetsCursorLocation) {
    // Given

    // When
    entry.text(L"Foo");

    // Then
    EXPECT_EQ(3, entry.cursor());
}

TEST_F(TextEntryWidget, typingCharMovesCursorForward) {
    // Given
    kevent.key = 'a';

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_EQ(1, entry.cursor());
}

TEST_F(TextEntryWidget, typingBackspaceMovesCursorsBackwards) {
    // Given
    entry.text(L"Foo");
    kevent.key = KEY_BACKSPACE;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_EQ(2, entry.cursor());
}

TEST_F(TextEntryWidget, renderDrawsCursorPosAgainIfFocus) {
    // Given
    entry.text(L"Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('_'), _, _))
        .Times(AnyNumber());
    EXPECT_CALL(*context,
                drawChar(Eq(entry.cursor()), _, TypedEq<wchar_t>(L'█'), _, _))
        .Times(1);

    entry.moveFocusForward();

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, renderDesntDrawCursorIfNoFocus) {
    // Given
    entry.text(L"Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('_'), _, _))
        .Times(AnyNumber());
    EXPECT_CALL(*context,
                drawChar(Eq(entry.cursor()), _, TypedEq<wchar_t>('_'), _, _))
        .Times(1);

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, typingBackspaceOnEmptyTextDoesntMoveCursors) {
    // Given
    entry.text(L"");
    kevent.key = KEY_BACKSPACE;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_EQ(0, entry.cursor());
}

TEST_F(TextEntryWidget, typingLeftMovesCursorBackwards) {
    // Given
    entry.text(L"Foo");
    kevent.key = KEY_LEFT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(2, entry.cursor());
}

TEST_F(TextEntryWidget, typingLeftDoesntMoveCursorAtZero) {
    // Given
    entry.text(L"");
    kevent.key = KEY_LEFT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(0, entry.cursor());
}

TEST_F(TextEntryWidget, typingRightMovesCursorForwards) {
    // Given
    entry.text(L"Foo");
    entry.cursor(1);
    kevent.key = KEY_RIGHT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(2, entry.cursor());
}

TEST_F(TextEntryWidget, typingRightDoesntMoveCursorAtEnd) {
    // Given
    entry.text(L"Foo");
    kevent.key = KEY_RIGHT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(3, entry.cursor());
}

TEST_F(TextEntryWidget, pressingKeyWhenCursorInWordAddsCharAtThatPosition) {
    // Given
    entry.text(L"Bar");
    entry.cursor(2);
    kevent.key = 'b';

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(3, entry.cursor());
    EXPECT_EQ(L"Babr", entry.text());
}

TEST_F(TextEntryWidget, pressingBackspaceWhenCursorInWordDeletesThatCharacter) {
    // Given
    entry.text(L"Bar");
    entry.cursor(2);
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(1, entry.cursor());
    EXPECT_EQ(L"Br", entry.text());
}

TEST_F(TextEntryWidget, settingTextFiresCallback) {
    // Given
    bool called = false;
    entry.onTextChanged = [&called](TextEntry&) { called = true; };

    // When
    entry.text(L"Bar");

    // Then
    EXPECT_TRUE(called);
}

TEST_F(TextEntryWidget, typingPrintableCharFiresCallback) {
    // Given
    bool called = false;
    entry.onTextChanged = [&called](TextEntry&) { called = true; };

    kevent.key = 'a';

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(called);
}

TEST_F(TextEntryWidget, erasingCharacterFiresCallback) {
    // Given
    bool called = false;
    entry.onTextChanged = [&called](TextEntry&) { called = true; };

    entry.text(L"Bar");
    kevent.key = KEY_BACKSPACE;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(called);
}

TEST_F(TextEntryWidget, pressingEnterCallsCallbackIfSet) {
    // Given
    bool called = false;
    entry.onSubmit = [&called](TextEntry&) { called = true; };

    kevent.key = KEY_ENTER;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(called);
}

TEST_F(TextEntryWidget, pressingEnterIgnoresCallbackIfNotSet) {
    // Given
    entry.onSubmit = nullptr;
    kevent.key = KEY_ENTER;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
}

TEST_F(TextEntryWidget, mouseClickInWordMovesCursorToThatChar) {
    // Given
    entry.text(L"Foo");
    entry.cursor(0);

    mevent.x = 2;

    // When
    bool handled = entry.handleMouseClick(mevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(2, entry.cursor());
}
// Pressing mouse, moves cursor
