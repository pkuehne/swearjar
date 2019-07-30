#include "screen.h"
#include "panel.h"

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
    // initscr();            // Start curses mode
    // raw();                // Line buffering disabled
    // keypad(stdscr, TRUE); // We get F1, F2 etc...
    // noecho();             // Don't echo() while we do getch
}

void Screen::run() {
    // mvprintw(5, 15, "Hello");
    int ch = m_curses->getchar();
}

std::shared_ptr<Panel> Screen::createPanel(unsigned int height,
                                           unsigned int width, unsigned int y,
                                           unsigned int x) {
    unsigned int id = m_curses->newwin(height, width, y, x);
    auto panel = std::make_shared<Panel>(id);
    m_panels[id] = panel;
    return panel;
}

} // namespace SwearJar