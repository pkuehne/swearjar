#pragma once

#include "curses_interface.h"
#include <map>
#include <ncursesw/ncurses.h>
#include <vector>

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    CursesWrapper();
    ~CursesWrapper() {
    }
    void initscr() override;
    void raw() override;
    void noecho() override;
    void keypad() override;
    void endwin() override;
    bool has_colors() override;
    void start_color() override;
    void enable_mouse() override;
    MouseEvent mouse_event() override;
    void init_pair(short pair, short fore, short back) override;
    short get_color(short fg, short bg) override;
    void color_on(short pair) override;
    void color_off(short pair) override;
    void reverse_on() override;
    void reverse_off() override;
    void blink_on() override;
    void blink_off() override;
    void wbkgd(short pair);
    void get_screen_size(int& height, int& width) override;

    unsigned int newwin(int h, int w, int y, int x) override;
    void mvwin(int y, int x) override;
    void wresize(int h, int w) override;
    void mvwprintw(int y, int x, const std::wstring& string) const override;
    void mvaddch_(int y, int x, char c) const override;

    int getchar() override;
    void refresh() override;
    void wrefresh() override;
    void touchwin_() override;

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
