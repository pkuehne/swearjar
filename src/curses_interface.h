#pragma once
#include <memory>
#include <spdlog/spdlog.h>
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
    virtual void reverse_on() {}
    virtual void reverse_off() {}
    virtual void wbkgd(short pair) {}
    virtual void get_screen_size(int& height, int& width) {}

    virtual int getchar() = 0;
    virtual void mvwprintw(int y, int x, const std::string& string) {}
    virtual void mvaddch_(int y, int x, char c) const {
        spdlog::error("Called base function mvaddch_");
    }
    virtual unsigned int newwin(int h, int w, int y, int x) = 0;
    virtual void refresh() {}
    virtual void wrefresh() {}
    virtual void currentWindow(unsigned int newWin){};
    virtual unsigned int currentWindow() = 0;
};

using CIptr = std::shared_ptr<CursesInterface>;

} // namespace SwearJar
