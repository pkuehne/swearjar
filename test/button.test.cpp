#include "button.h"
#include "curses.mock.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

class ButtonWidget : public Test {
public:
    void SetUp() {
    }

protected:
    Button b{"testButton"};
    std::shared_ptr<MockCurses> curses{
        std::make_shared<NiceMock<MockCurses>>()};
    std::unique_ptr<MockRenderContext> context{
        std::make_unique<NiceMock<MockRenderContext>>(*curses)};
};

TEST_F(ButtonWidget, canTakeFocusByDefault) {
    // Given

    // When

    // Then
    EXPECT_TRUE(b.canTakeFocus());
}

TEST_F(ButtonWidget, setTextSetsWide) {
    // Given

    // When
    b.text("Test Title");

    // Then
    EXPECT_EQ(L"Test Title", b.text());
}

TEST_F(ButtonWidget, renderClearsTheAreaOfTheButton) {
    // Given
    b.text(L"Foo");
    b.height(2);

    EXPECT_CALL(*context, clearArea(0, 0, b.width(), b.height(), _, _))
        .Times(1);

    // When
    b.render(*context);
}

TEST_F(ButtonWidget, renderDisplaysText) {
    // Given
    b.text(L"Foo");

    EXPECT_CALL(*context,
                drawText(_, _, TypedEq<const std::wstring&>(b.text()), _, _))
        .Times(1);

    // When
    b.render(*context);
}

TEST_F(ButtonWidget, keyPressCallsCallbackOnEnter) {
    // Given
    bool pressed = false;

    b.onPressed = [&pressed](Button&) { pressed = true; };

    KeyEvent e;
    e.key = 10;

    // When
    bool handled = b.handleKeyPress(e);

    // Then
    EXPECT_TRUE(handled);
    EXPECT_TRUE(pressed);
}

TEST_F(ButtonWidget, keyPressDoesNothingIfNotEnter) {
    // Given
    bool pressed = false;

    b.onPressed = [&pressed](Button&) { pressed = true; };

    KeyEvent e;
    e.key = 'f';

    // When
    bool handled = b.handleKeyPress(e);

    // Then
    EXPECT_FALSE(handled);
    EXPECT_FALSE(pressed);
}

TEST_F(ButtonWidget, keyPressDoesNotThrowIfNoFunctionIsSet) {
    // Given
    b.onPressed = nullptr;

    KeyEvent e;
    e.key = 'f';

    // When
    EXPECT_NO_THROW(b.handleKeyPress(e));
}

TEST_F(ButtonWidget, handleMouseClickCallsCallbackOnEnter) {
    // Given
    bool pressed = false;

    b.onPressed = [&pressed](Button&) { pressed = true; };

    // When
    bool handled = b.handleMouseClick(MouseEvent());

    // Then
    EXPECT_TRUE(handled);
    EXPECT_TRUE(pressed);
}

TEST_F(ButtonWidget, handleMouseClickDoesNotThrowIfNoFunctionIsSet) {
    // Given
    Button b("testButton");
    b.onPressed = nullptr;

    // When
    EXPECT_NO_THROW(b.handleMouseClick(MouseEvent()));
}
