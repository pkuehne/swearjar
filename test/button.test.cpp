#include "button.h"
#include "curses.mock.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(Button, renderClearsTheWidthOfTheButton) {
    // Given
    Button b("testButton");
    b.text(L"Foo");

    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawText(_, _, _, _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(L" "), _, _)).Times(1);

    // When
    b.render(*context);
}

TEST(Button, renderDisplaysText) {
    // Given
    Button b("testButton");
    b.text(L"Foo");

    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawText(_, _, _, _, _)).Times(1);
    EXPECT_CALL(*context, drawText(_, _, Eq(b.text()), _, _)).Times(1);

    // When
    b.render(*context);
}

TEST(Button, keyPressCallsCallbackOnEnter) {
    // Given
    bool pressed = false;

    Button b("testButton");
    b.onPressed = [&pressed](Button&) { pressed = true; };

    KeyEvent e;
    e.key = 10;

    // When
    bool handled = b.handleKeyPress(e);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_TRUE(pressed);
}

TEST(Button, keyPressDoesNothingIfNotEnter) {
    // Given
    bool pressed = false;

    Button b("testButton");
    b.onPressed = [&pressed](Button&) { pressed = true; };

    KeyEvent e;
    e.key = 'f';

    // When
    bool handled = b.handleKeyPress(e);

    // Then
    EXPECT_FALSE(handled);
    EXPECT_FALSE(pressed);
}

TEST(Button, keyPressDoesNotThrowIfNoFunctionIsSet) {
    // Given
    Button b("testButton");
    b.onPressed = nullptr;

    KeyEvent e;
    e.key = 'f';

    // When
    EXPECT_NO_THROW(b.handleKeyPress(e));
}

TEST(Button, handleMouseClickCallsCallbackOnEnter) {
    // Given
    bool pressed = false;

    Button b("testButton");
    b.onPressed = [&pressed](Button&) { pressed = true; };

    // When
    bool handled = b.handleMouseClick(MouseEvent());

    // Then
    EXPECT_TRUE(handled);
    EXPECT_TRUE(pressed);
}

TEST(Button, handleMouseClickDoesNotThrowIfNoFunctionIsSet) {
    // Given
    Button b("testButton");
    b.onPressed = nullptr;

    // When
    EXPECT_NO_THROW(b.handleMouseClick(MouseEvent()));
}
