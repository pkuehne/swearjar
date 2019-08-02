#pragma once

#include "curses_interface.h"
#include <ncurses.h>
#include <vector>

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    ~CursesWrapper() {}
    void initscr();
    void raw();
    void noecho();
    void keypad();
    void endwin();

    unsigned int newwin(int h, int w, int y, int x);
    void mvwprintw(int y, int x, const std::string& string);
    void mvaddch_(int y, int x, char c);

    int getchar();
    void refresh();
    void wrefresh();

    void currentWindow(unsigned int newWin) { m_currentWindow = newWin; }
    unsigned int currentWindow() { return m_currentWindow; }

private:
    std::vector<WINDOW*> m_windows;
    unsigned int m_currentWindow = 0;
};

} // namespace SwearJar