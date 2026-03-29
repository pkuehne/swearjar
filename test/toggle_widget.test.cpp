#include "checkbox.h"
#include "curses.mock.h"
#include "render_context.mock.h"
#include "toggle_widget.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace ::testing;
using namespace SwearJar;

// Use Checkbox as a concrete ToggleWidget for testing the shared base behaviour.
class ToggleWidgetBase : public Test {
protected:
    Checkbox widget{"twTest"};
    KeyEvent kevent;
    MouseEvent mevent;
};

TEST_F(ToggleWidgetBase, canTakeFocus) {
    EXPECT_TRUE(widget.canTakeFocus());
}

TEST_F(ToggleWidgetBase, canSetWideText) {
    widget.text(L"Hello");
    EXPECT_EQ(L"Hello", widget.text());
}

TEST_F(ToggleWidgetBase, canSetNarrowText) {
    widget.text(std::string("Hello"));
    EXPECT_EQ(L"Hello", widget.text());
}

TEST_F(ToggleWidgetBase, settingTextSetsMinWidth) {
    widget.text(L"Hi");
    EXPECT_EQ(6u, widget.requiredWidth()); // text.size() + 4
}

TEST_F(ToggleWidgetBase, enterKeyCallsToggle) {
    kevent.key = 10;
    bool toggled = widget.enabled();
    widget.handleKeyPress(kevent);
    EXPECT_NE(toggled, widget.enabled());
}

TEST_F(ToggleWidgetBase, otherKeyDoesNothing) {
    kevent.key = 'x';
    bool toggled = widget.enabled();
    bool handled = widget.handleKeyPress(kevent);
    EXPECT_FALSE(handled);
    EXPECT_EQ(toggled, widget.enabled());
}

TEST_F(ToggleWidgetBase, mouseClickCallsToggle) {
    bool toggled = widget.enabled();
    widget.handleMouseClick(mevent);
    EXPECT_NE(toggled, widget.enabled());
}

TEST_F(ToggleWidgetBase, enterKeyFiresOnToggleCallback) {
    kevent.key = 10;
    bool called = false;
    widget.onToggle = [&called](ToggleWidget&) { called = true; };
    widget.handleKeyPress(kevent);
    EXPECT_TRUE(called);
}

TEST_F(ToggleWidgetBase, mouseClickFiresOnToggleCallback) {
    bool called = false;
    widget.onToggle = [&called](ToggleWidget&) { called = true; };
    widget.handleMouseClick(mevent);
    EXPECT_TRUE(called);
}

TEST_F(ToggleWidgetBase, onToggleNotCalledIfNotSet) {
    kevent.key = 10;
    widget.onToggle = nullptr;
    EXPECT_NO_THROW(widget.handleKeyPress(kevent));
}
