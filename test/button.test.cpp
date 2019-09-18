#include "button.h"
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(Button, keyPressCallsCallbackOnEnter) {
    // Given
    bool pressed = false;

    Button b("testButton");
    b.onPressed = [&pressed](Button&) { pressed = true; };

    // When
    bool handled = b.handleKeyPress(10);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_TRUE(pressed);
}

TEST(Button, keyPressDoesNothingIfNotEnter) {
    // Given
    bool pressed = false;

    Button b("testButton");
    b.onPressed = [&pressed](Button&) { pressed = true; };

    // When
    bool handled = b.handleKeyPress('f');

    // Then
    EXPECT_FALSE(handled);
    EXPECT_FALSE(pressed);
}

TEST(Button, keyPressDoesNotThrowIfNoFunctionIsSet) {
    // Given
    Button b("testButton");
    b.onPressed = nullptr;

    // When
    EXPECT_NO_THROW(b.handleKeyPress('f'));
}
