#include "screen.h"
#include "panel.h"
#include <iostream>

namespace SwearJar {

Screen::Screen(std::shared_ptr<CursesInterface> curses) : m_curses(curses) {
    //
}

Screen::~Screen() { m_curses->endwin(); }

void Screen::initialize() {
    m_curses->initscr();
    m_curses->raw();
    m_curses->noecho();
    m_curses->keypad();
}

void Screen::run() {
    int ch = 0;
    m_curses->refresh();

    while (!m_quit) {
        refreshDirtyWidgets();
        ch = m_curses->getchar();
        m_quit = (ch == 'q');
        unhandledKeys(ch);
    }
}

std::shared_ptr<Panel> Screen::createPanel(unsigned int height,
                                           unsigned int width, unsigned int y,
                                           unsigned int x) {
    unsigned int id = m_curses->newwin(height, width, y, x);
    auto panel = std::make_shared<Panel>(id, m_curses);
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