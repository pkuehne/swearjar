#include "app.h"

namespace SwearJar {

App::App(std::shared_ptr<CursesInterface> curses) : m_curses(curses) {
    //
}

App::~App() { m_curses->endwin(); }

void App::initialize() {
    m_curses->initscr();
    m_curses->raw();
    m_curses->noecho();
    m_curses->keypad();
    // initscr();            // Start curses mode
    // raw();                // Line buffering disabled
    // keypad(stdscr, TRUE); // We get F1, F2 etc...
    // noecho();             // Don't echo() while we do getch
}

void App::run() {
    // mvprintw(5, 15, "Hello");
    int ch = m_curses->getchar();
}

} // namespace SwearJar