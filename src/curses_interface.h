#pragma once
#include <memory>
#include <string>

namespace SwearJar {

class CursesInterface {
public:
    virtual ~CursesInterface(){};
    virtual void initscr(){};
    virtual void raw() {}
    virtual void noecho() {}
    virtual void keypad() {}
    virtual void endwin() {}
    virtual bool has_colors() = 0;
    virtual void start_color() {}
    virtual void init_pair(short pair, short fore, short back) {}
    virtual void color_on(short pair) {}
    virtual void color_off(short pair) {}
    virtual short get_color(short fg, short bg) = 0;
    virtual void wbkgd(short pair) {}

    virtual int getchar() = 0;
    virtual void mvwprintw(int y, int x, const std::string& string) {}
    virtual void mvaddch_(int y, int x, char c) {}
    virtual unsigned int newwin(int h, int w, int y, int x) = 0;
    virtual void refresh() {}
    virtual void wrefresh() {}
    virtual void currentWindow(unsigned int newWin){};
    virtual unsigned int currentWindow() = 0;
};

using CIptr = std::shared_ptr<CursesInterface>;

} // namespace SwearJar