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

    // When
    entry.text("Test Test");

    // Then
    EXPECT_EQ("Test Test", entry.text());
}

TEST_F(TextEntryWidget, rendersPlaceholderWhenNoText) {
    // Given
    EXPECT_CALL(*context, drawChar(_, _, Eq('_'), _, _)).Times(entry.width());
    EXPECT_CALL(*context, drawText(_, _, Eq(""), _, _));

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, rendersTextWhenSetPlusPlaceholders) {
    // Given
    entry.text("TEST");
    EXPECT_CALL(*context, drawChar(_, _, Eq('_'), _, _)).Times(6);
    EXPECT_CALL(*context, drawText(_, _, Eq(entry.text()), _, _));

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
    EXPECT_EQ(entry.text(), "a");
}

TEST_F(TextEntryWidget, pressingUnprintableKeyDoesNothing) {
    // Given
    kevent.key = '\t';

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_FALSE(handled);
    EXPECT_EQ(entry.text(), "");
}

TEST_F(TextEntryWidget, pressingBackspaceKeyRemovesCharFromText) {
    // Given
    entry.text("Foo");
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(entry.text(), "Fo");
}

TEST_F(TextEntryWidget, pressingBackspaceKeyDoesNothingOnEmptyString) {
    // Given
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(entry.text(), "");
}

TEST_F(TextEntryWidget, rendersBlinkIfHasFocus) {
    // Given
    entry.text("Foo");
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
    entry.text("Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, blink(Eq(true))).Times(0);
    EXPECT_CALL(*context, blink(Eq(false))).Times(0);

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, settingCursorUpdatesItsPosition) {
    // Given
    EXPECT_EQ(0, entry.cursor());

    // When
    entry.cursor(5);

    // Then
    EXPECT_EQ(5, entry.cursor());
}

TEST_F(TextEntryWidget, settingTextSetsCursorLocation) {
    // Given

    // When
    entry.text("Foo");

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
    entry.text("Foo");
    kevent.key = KEY_BACKSPACE;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_EQ(2, entry.cursor());
}

TEST_F(TextEntryWidget, rendersDrawsCursorPosAgainIfFocus) {
    // Given
    entry.text("Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, drawChar(_, _, Eq('_'), _, _)).Times(AnyNumber());
    EXPECT_CALL(*context, drawChar(Eq(entry.cursor()), _, Eq('_'), _, _))
        .Times(2);

    entry.moveFocusForward();

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, rendersDesntDrawCursorIfNoFocus) {
    // Given
    entry.text("Foo");
    context = std::make_unique<NiceMock<MockRenderContext>>(*curses);
    EXPECT_CALL(*context, drawChar(_, _, Eq('_'), _, _)).Times(AnyNumber());
    EXPECT_CALL(*context, drawChar(Eq(entry.cursor()), _, Eq('_'), _, _))
        .Times(1);

    // When
    entry.render(*context);

    // Then
}

TEST_F(TextEntryWidget, typingBackspaceOnEmptyTextDoesntMoveCursors) {
    // Given
    entry.text("");
    kevent.key = KEY_BACKSPACE;

    // When
    entry.handleKeyPress(kevent);

    // Then
    EXPECT_EQ(0, entry.cursor());
}

TEST_F(TextEntryWidget, typingLeftMovesCursorBackwards) {
    // Given
    entry.text("Foo");
    kevent.key = KEY_LEFT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(2, entry.cursor());
}

TEST_F(TextEntryWidget, typingLeftDoesntMoveCursorAtZero) {
    // Given
    entry.text("");
    kevent.key = KEY_LEFT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(0, entry.cursor());
}

TEST_F(TextEntryWidget, typingRightMovesCursorForwards) {
    // Given
    entry.text("Foo");
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
    entry.text("Foo");
    kevent.key = KEY_RIGHT;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(3, entry.cursor());
}

TEST_F(TextEntryWidget, pressingKeyWhenCursorInWordAddsCharAtThatPosition) {
    // Given
    entry.text("Bar");
    entry.cursor(2);
    kevent.key = 'b';

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(3, entry.cursor());
    EXPECT_EQ("Babr", entry.text());
}

TEST_F(TextEntryWidget, pressingBackspaceWhenCursorInWordDeletesThatCharacter) {
    // Given
    entry.text("Bar");
    entry.cursor(2);
    kevent.key = KEY_BACKSPACE;

    // When
    bool handled = entry.handleKeyPress(kevent);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_EQ(1, entry.cursor());
    EXPECT_EQ("Br", entry.text());
}

TEST_F(TextEntryWidget, settingTextFiresCallback) {
    // Given
    bool called = false;
    entry.onTextChanged = [&called](TextEntry&) { called = true; };

    // When
    entry.text("Bar");

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

    entry.text("Bar");
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

// Pressing mouse, moves cursor
