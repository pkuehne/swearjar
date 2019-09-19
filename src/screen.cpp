#include "screen.h"
#include "window.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace {
const int KEY_TAB = 9;
const int KEY_ENTER = 10;
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
}

void Screen::run() {
    int ch = 0;
    m_curses->refresh();

    (*m_windows.rbegin())->baseWidget().moveFocusForward();
    while (!m_quit) {
        refreshWindows();
        ch = m_curses->getchar();
        spdlog::debug("Handling key {}", ch);
        if (ch == KEY_TAB) {
            (*m_windows.rbegin())->baseWidget().moveFocusForward();
            continue;
        }
        if (ch == 'q') {
            m_quit = true;
            continue;
        }
        bool handled = (*m_windows.rbegin())->baseWidget().handleKeyPress(ch);
        if (!handled) {
            unhandledKeys(ch);
        }
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

} // namespace SwearJar
