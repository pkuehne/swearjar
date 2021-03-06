#include "screen.h"
#include "panel.h"
#include <iostream>
#include <spdlog/spdlog.h>

namespace SwearJar {

Screen::Screen(CIptr curses) : m_curses(curses) {
    spdlog::info("Screen initialized");
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

    m_panels.begin()->second->widget()->moveFocusForward();
    while (!m_quit) {
        refreshDirtyWidgets();
        ch = m_curses->getchar();
        // spdlog::info("Handling {}", ch);
        if (ch == 9) {
            m_panels.begin()->second->widget()->moveFocusForward();
            continue;
        }
        if (ch == 'q') {
            m_quit = true;
            continue;
        }
        bool handled = m_panels.begin()->second->widget()->handleKeyPress(ch);
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

std::shared_ptr<Panel> Screen::createPanel(unsigned int x, unsigned int y,
                                           unsigned int width,
                                           unsigned int height) {
    unsigned int id = m_curses->newwin(height, width, y, x);
    auto panel = std::make_shared<Panel>(id, m_curses, height, width);
    m_panels[id] = panel;
    return panel;
}

void Screen::refreshDirtyWidgets() {
    for (auto iter : m_panels) {
        auto panel = iter.second;
        panel->refreshDirtyWidgets();
    }
    m_curses->refresh();
}

} // namespace SwearJar
