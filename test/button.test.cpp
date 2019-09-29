#include "button.h"
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

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
