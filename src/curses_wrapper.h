#pragma once

#include "curses_interface.h"
#include <map>
#include <ncurses.h>
#include <vector>

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    CursesWrapper();
    ~CursesWrapper() {
    }
    void initscr();
    void raw();
    void noecho();
    void keypad();
    void endwin();
    bool has_colors();
    void start_color();
    void enable_mouse();
    MouseEvent mouse_event();
    void init_pair(short pair, short fore, short back);
    short get_color(short fg, short bg);
    void color_on(short pair) override;
    void color_off(short pair) override;
    void reverse_on() override;
    void reverse_off() override;
    void blink_on() override;
    void blink_off() override;
    void wbkgd(short pair);
    void get_screen_size(int& height, int& width);

    unsigned int newwin(int h, int w, int y, int x);
    void mvwprintw(int y, int x, const std::string& string);
    void mvaddch_(int y, int x, char c) const;

    int getchar();
    void refresh();
    void wrefresh();
    void touchwin_();

    void currentWindow(unsigned int newWin) {
        m_currentWindow = newWin;
    }
    unsigned int currentWindow() {
        return m_currentWindow;
    }

    void setupResizeHandler();

private:
    std::vector<WINDOW*> m_windows;
    unsigned int m_currentWindow = 0;
    short m_colorMax = 0;
    std::map<std::pair<short, short>, short> m_colorMap;
};

} // namespace SwearJar
