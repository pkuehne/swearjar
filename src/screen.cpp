#include "screen.h"
#include "window.h"
#include <iostream>
#include <spdlog/spdlog.h>

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
    clearScreen();
}

void Screen::run() {
    int ch = 0;
    m_curses->refresh();

    m_windows.begin()->second->baseWidget().moveFocusForward();
    while (!m_quit) {
        refreshDirtyWidgets();
        ch = m_curses->getchar();
        spdlog::debug("Handling key {}", ch);
        if (ch == 9) {
            m_windows.begin()->second->baseWidget().moveFocusForward();
            continue;
        }
        if (ch == 'q') {
            m_quit = true;
            continue;
        }
        bool handled =
            m_windows.begin()->second->baseWidget().handleKeyPress(ch);
        if (!handled) {
            unhandledKeys(ch);
        }
    }
}

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
    int height = 0, width = 0;
    m_curses->get_screen_size(height, width);

    return createWindow(0, 0, width, height);
}

Window& Screen::createWindow(unsigned int x, unsigned int y, unsigned int width,
                             unsigned int height) {
    unsigned int id = m_curses->newwin(height, width, y, x);
    m_windows[id] = std::make_unique<Window>(id, m_curses, height, width);
    return *m_windows[id];
}

void Screen::refreshDirtyWidgets() {
    for (auto& iter : m_windows) {
        auto& window = iter.second;
        window->refreshDirtyWidgets();
    }
    m_curses->refresh();
}

} // namespace SwearJar
