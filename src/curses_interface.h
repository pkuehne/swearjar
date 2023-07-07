#pragma once

#include <memory>
#include <string>

namespace SwearJar {

struct MouseEvent {
    unsigned int device = 0;
    unsigned int x = 0;
    unsigned int y = 0;
    bool leftClicked = false;
    bool rightClicked = false;
};

struct KeyEvent {
    int key = 0;
};

const int KEY_TAB = 9;
const int KEY_ENTER = 10;
const int KEY_DOWN = 258;
const int KEY_UP = 259;
const int KEY_LEFT = 260;
const int KEY_RIGHT = 261;
const int KEY_BACKSPACE = 263;
const int KEY_PGDOWN = 338;
const int KEY_PGUP = 339;
const int KEY_MOUSE = 409;
const int KEY_RESIZE = 410;

class CursesInterface {
public:
    virtual ~CursesInterface() = default;
    virtual void initscr() = 0;
    virtual void raw() = 0;
    virtual void noecho() = 0;
    virtual void nodelay(bool)  = 0;
    virtual void keypad() = 0;
    virtual void endwin() = 0;
    virtual void start_color() = 0;
    virtual void enable_mouse() = 0;
    virtual MouseEvent mouse_event() {
        return {};
    }
    virtual void init_pair(short pair, short fg, short bg) = 0;
    virtual bool has_colors() = 0;
    virtual void color_on(short pair) = 0;
    virtual void color_off(short pair) = 0;
    virtual short get_color(short fg, short bg) = 0;
    virtual void reverse_on() = 0;
    virtual void reverse_off() = 0;
    virtual void blink_on() = 0;
    virtual void blink_off() = 0;

    virtual void wbkgd(short pair) = 0;
    virtual void get_screen_size(int* height, int* width) = 0;

    virtual int getchar() = 0;
    virtual void mvwprint(int y, int x, const std::string& string) const = 0;
    virtual void mvwprintw(int y, int x, const std::wstring& string) const = 0;
    virtual void mvaddch_(int y, int x, char c) const = 0;
    virtual void mvaddwch_(int y, int x, wchar_t ch) const = 0;

    virtual unsigned int newwin(int h, int w, int y, int x) = 0;
    virtual void refresh() = 0;
    virtual void wrefresh() = 0;
    virtual void touchwin_() = 0;
    virtual void wresize(int h, int w) = 0;
    virtual void mvwin(int y, int x) = 0;

    virtual void currentWindow(unsigned int newWin) = 0;
    virtual unsigned int currentWindow() = 0;
};

} // namespace SwearJar
