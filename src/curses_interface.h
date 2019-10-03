#pragma once
#include <memory>
#include <spdlog/spdlog.h>
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

namespace {
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
} // namespace

class CursesInterface {
public:
    virtual ~CursesInterface(){};
    virtual void initscr(){};
    virtual void raw() {
    }
    virtual void noecho() {
    }
    virtual void keypad() {
    }
    virtual void endwin() {
    }
    virtual bool has_colors() = 0;
    virtual void start_color() {
    }
    virtual void enable_mouse() {
    }
    virtual MouseEvent mouse_event() {
        return MouseEvent();
    }
    virtual void init_pair(short pair, short fore, short back) {
    }

    virtual void color_on(short pair) = 0;
    virtual void color_off(short pair) = 0;
    virtual short get_color(short fg, short bg) = 0;
    virtual void reverse_on() = 0;
    virtual void reverse_off() = 0;
    virtual void blink_on() = 0;
    virtual void blink_off() = 0;

    virtual void wbkgd(short pair) {
    }
    virtual void get_screen_size(int& height, int& width) {
    }

    virtual int getchar() = 0;
    virtual void mvwprintw(int y, int x, const std::string& string) {
    }
    virtual void mvaddch_(int y, int x, char c) const {
        spdlog::error("Called base function mvaddch_");
    }
    virtual unsigned int newwin(int h, int w, int y, int x) = 0;
    virtual void refresh() {
    }
    virtual void wrefresh() {
    }
    virtual void touchwin_() {
    }
    virtual void currentWindow(unsigned int newWin){};
    virtual unsigned int currentWindow() = 0;
};

} // namespace SwearJar
