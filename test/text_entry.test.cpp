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

// blink on and off is called when focus is set
// blink on and off is not called when focus is not set
// typing left moves cursor forwards
// typing right moves cursor backwards
// typing left moves cursor only to end of text
// typing right moves cursor only to beg of text
// when text empty, cursor cant move
// typing when curor in middle of text inserts at that pos
// typing enter calls callback if set
// typing enter does nothing if callback not set
// typing a key calls callback if set
// typing a key does nothing if callback not set
