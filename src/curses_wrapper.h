#pragma once

#include "curses_interface.h"
#include <ncurses.h>
#include <vector>

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    void initscr();
    void raw();
    void noecho();
    void keypad();
    void endwin();

    unsigned int newwin(int h, int w, int y, int x);

    int getchar();

private:
    std::vector<WINDOW*> m_windows;
};

} // namespace SwearJar