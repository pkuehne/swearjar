#include "screen.h"
#include "window.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace {
const int KEY_TAB = 9;
const int KEY_ENTER = 10;
const int KEY_MOUSE = 409;
} // namespace

namespace SwearJar {

Screen::Screen(CIptr curses) : m_curses(curses) {
    spdlog::debug("Screen initialized");
}

Screen::~Screen() { m_curses->endwin(); }

void Screen::initialize() {
    m_curses->initscr();
    m_curses->raw();
    m_curses->noecho();
    m_curses->keypad();
    if (m_curses->has_colors()) {
        m_curses->start_color();
    }
    m_curses->enable_mouse();
}

void Screen::run() {
    int ch = 0;
    m_curses->refresh();

    (*m_windows.rbegin())->baseWidget().moveFocusForward();
    while (!m_quit) {
        refreshWindows();
        ch = m_curses->getchar();
        if (ch == KEY_MOUSE) {
            MouseEvent event = m_curses->mouse_event();
            handleMouse(event);
            continue;
        }
        KeyEvent event;
        event.key = ch;
        handleKeys(event);
    }
}

void Screen::popWindow() {
    if (m_windows.size() == 0) {
        return;
    }
    m_windows.pop_back();
}

void Screen::refreshWindows() {
    for (auto& window : m_windows) {
        window->refresh();
    }
    m_curses->refresh();
}

void Screen::handleKeys(const KeyEvent& event) {
    spdlog::debug("Handling key {}", event.key);
    if (event.key == KEY_TAB) {
        (*m_windows.rbegin())->baseWidget().moveFocusForward();
        return;
    }
    bool handled = (*m_windows.rbegin())->baseWidget().handleKeyPress(event);
    if (!handled) {
        unhandledKeys(event);
    }
}

void Screen::handleMouse(const MouseEvent& event) {
    spdlog::debug("device: {} x = {} y = {} l = {} r = {}", event.device,
                  event.x, event.y, event.leftClicked, event.rightClicked);
    if (!event.leftClicked) {
        return;
    }
    auto& topWin = *(*m_windows.rbegin());
    if (topWin.contains(event.x, event.y)) {
        // Convert from scren coordinates to window coordinates
        MouseEvent l_event(event);
        l_event.x -= topWin.x() - 1;
        l_event.y -= topWin.y() - 1;
        spdlog::info("handling button click @ ({}, {})", l_event.x, l_event.y);
        topWin.baseWidget().handleMouseClick(l_event);
    }
}
} // namespace SwearJar
