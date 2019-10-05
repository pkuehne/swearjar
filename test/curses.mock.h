#pragma once

#include "curses_interface.h"
#include <gmock/gmock.h>

class MockCurses : public SwearJar::CursesInterface {
public:
    MOCK_METHOD0(initscr, void());
    MOCK_METHOD0(raw, void());
    MOCK_METHOD0(noecho, void());
    MOCK_METHOD0(keypad, void());
    MOCK_METHOD0(endwin, void());
    MOCK_METHOD0(start_color, void());
    MOCK_METHOD0(enable_mouse, void());
    MOCK_METHOD0(getchar, int());
    MOCK_METHOD4(newwin, unsigned int(int, int, int, int));
    MOCK_METHOD0(currentWindow, unsigned int());
    MOCK_METHOD0(has_colors, bool());
    MOCK_METHOD3(init_pair, void(short pair, short fg, short bg));
    MOCK_METHOD2(get_color, short(short, short));
    MOCK_METHOD1(color_on, void(short));
    MOCK_METHOD1(color_off, void(short));
    MOCK_METHOD0(reverse_on, void());
    MOCK_METHOD0(reverse_off, void());
    MOCK_METHOD0(blink_on, void());
    MOCK_METHOD0(blink_off, void());
    MOCK_METHOD1(wbkgd, void(short pair));
    MOCK_CONST_METHOD3(mvwprint, void(int y, int x, const std::string& string));
    MOCK_CONST_METHOD3(mvwprintw,
                       void(int y, int x, const std::wstring& string));
    MOCK_CONST_METHOD3(mvaddch_, void(int, int, char));
    MOCK_CONST_METHOD3(mvaddwch_, void(int y, int x, wchar_t ch));
    MOCK_METHOD2(get_screen_size, void(int&, int&));
    MOCK_METHOD2(wresize, void(int, int));
    MOCK_METHOD2(mvwin, void(int, int));
    MOCK_METHOD0(refresh, void());
    MOCK_METHOD0(wrefresh, void());
    MOCK_METHOD0(touchwin_, void());
    MOCK_METHOD1(currentWindow, void(unsigned int newWin));
};
