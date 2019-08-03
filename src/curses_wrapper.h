#pragma once

#include "curses_interface.h"
#include <map>
#include <ncurses.h>
#include <vector>

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    CursesWrapper();
    ~CursesWrapper() {}
    void initscr();
    void raw();
    void noecho();
    void keypad();
    void endwin();
    bool has_colors();
    void start_color();
    void init_pair(short pair, short fore, short back);
    void color_on(short pair);
    void color_off(short pair);
    short get_color(short fg, short bg);
    void wbkgd(short pair);

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
    short m_colorMax = 0;
    std::map<std::pair<short, short>, short> m_colorMap;
};

} // namespace SwearJar