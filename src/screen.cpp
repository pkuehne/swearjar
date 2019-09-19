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

    m_windows.rbegin()->second->baseWidget().moveFocusForward();
    while (!m_quit) {
        refreshWindows();
        ch = m_curses->getchar();
        spdlog::debug("Handling key {}", ch);
        if (ch == KEY_TAB) {
            m_windows.rbegin()->second->baseWidget().moveFocusForward();
            continue;
        }
        if (ch == 'q') {
            m_quit = true;
            continue;
        }
        bool handled =
            m_windows.rbegin()->second->baseWidget().handleKeyPress(ch);
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

Window& Screen::createWindow() {
    int screenHeight = 0, screenWidth = 0;
    m_curses->get_screen_size(screenHeight, screenWidth);

    return createWindow(0, 0, screenWidth, screenHeight);
}

Window& Screen::createWindow(unsigned int width, unsigned int height) {
    int screenHeight = 0, screenWidth = 0;
    m_curses->get_screen_size(screenHeight, screenWidth);

    unsigned int x = (screenWidth / 2) - (width / 2);
    unsigned int y = (screenHeight / 2) - (height / 2);

    return createWindow(x, y, width, height);
}
Window& Screen::createWindow(unsigned int x, unsigned int y, unsigned int width,
                             unsigned int height) {
    unsigned int id = m_curses->newwin(height, width, y, x);
    m_windows[id] = std::make_unique<Window>(id, m_curses, height, width);
    return *m_windows[id];
}

void Screen::refreshWindows() {
    for (auto& iter : m_windows) {
        auto& window = iter.second;
        window->refresh();
    }
    m_curses->refresh();
}

} // namespace SwearJar
