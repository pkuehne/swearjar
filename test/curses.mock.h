#pragma once

#include "curses_interface.h"
#include <gmock/gmock.h>

class MockCurses : public SwearJar::CursesInterface {
public:
    MOCK_METHOD(void, initscr, (), (override));
    MOCK_METHOD(void, raw, (), (override));
    MOCK_METHOD(void, noecho, (), (override));
    MOCK_METHOD(void, nodelay, (bool), (override));
    MOCK_METHOD(void, keypad, (), (override));
    MOCK_METHOD(void, endwin, (), (override));
    MOCK_METHOD(void, start_color, (), (override));
    MOCK_METHOD(void, enable_mouse, (), (override));
    MOCK_METHOD(int, getchar, (), (override));
    MOCK_METHOD(unsigned int, newwin, (int, int, int, int), (override));
    MOCK_METHOD(unsigned int, currentWindow, (), (override));
    MOCK_METHOD(bool, has_colors, (), (override));
    MOCK_METHOD(void, init_pair, (short pair, short fg, short bg), (override));
    MOCK_METHOD(short, get_color, (short, short), (override));
    MOCK_METHOD(void, color_on, (short), (override));
    MOCK_METHOD(void, color_off, (short), (override));
    MOCK_METHOD(void, reverse_on, (), (override));
    MOCK_METHOD(void, reverse_off, (), (override));
    MOCK_METHOD(void, blink_on, (), (override));
    MOCK_METHOD(void, blink_off, (), (override));
    MOCK_METHOD(void, wbkgd, (short pair), (override));
    MOCK_METHOD(void, mvwprint, (int y, int x, const std::string& string),
                (override, const));
    MOCK_METHOD(void, mvwprintw, (int y, int x, const std::wstring& string),
                (override, const));
    MOCK_METHOD(void, mvaddch_, (int, int, char), (override, const));
    MOCK_METHOD(void, mvaddwch_, (int y, int x, wchar_t ch), (override, const));
    MOCK_METHOD(void, get_screen_size, (int*, int*), (override));
    MOCK_METHOD(void, wresize, (int, int), (override));
    MOCK_METHOD(void, mvwin, (int, int), (override));
    MOCK_METHOD(void, refresh, (), (override));
    MOCK_METHOD(void, wrefresh, (), (override));
    MOCK_METHOD(void, touchwin_, (), (override));
    MOCK_METHOD(void, currentWindow, (unsigned int newWin), (override));
};
