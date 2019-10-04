#include "checkbox.h"
#include "curses.mock.h"
#include "render_context.mock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

TEST(Checkbox, canTakeFocus) {
    // Given
    Checkbox box("chkTest");

    // Then
    EXPECT_TRUE(box.canTakeFocus());
}

TEST(Checkbox, togglesWhenSelectionKeyPressed) {
    // Given
    Checkbox box("chkTest");
    KeyEvent event;
    event.key = 10;
    bool enabled = box.enabled();

    // When
    box.handleKeyPress(event);

    // Then
    EXPECT_NE(enabled, box.enabled());
}

TEST(Checkbox, togglesWhenClicked) {
    // Given
    Checkbox box("chkTest");
    MouseEvent event;

    bool enabled = box.enabled();

    // When
    box.handleMouseClick(event);

    // Then
    EXPECT_NE(enabled, box.enabled());
}

TEST(Checkbox, doesntRenderXWhenNotEnabled) {
    // Given
    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('X'), _, _)).Times(0);

    Checkbox box("chkTest");

    // When
    box.render(*context);
}

TEST(Checkbox, rendersXWhenEnabled) {
    // Given
    auto curses = std::make_shared<NiceMock<MockCurses>>();
    auto context = std::make_unique<NiceMock<MockRenderContext>>(*curses);

    EXPECT_CALL(*context, drawChar(_, _, TypedEq<wchar_t>('X'), _, _)).Times(1);

    Checkbox box("chkTest");
    box.enabled(true);

    // When
    box.render(*context);
}
