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
    // clearScreen();
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

/// @note potentially unused
void Screen::clearScreen() {
    m_curses->currentWindow(0);
    int height, width;
    m_curses->get_screen_size(height, width);

    m_curses->color_on(m_curses->get_color(8, 0));
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            m_curses->mvaddch_(y, x, ' ');
        }
    }
    m_curses->color_off(m_curses->get_color(8, 0));

    m_curses->refresh();
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
