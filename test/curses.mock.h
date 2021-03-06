#pragma once

#include "curses_interface.h"
#include <gmock/gmock.h>

class MockCurses : public SwearJar::CursesInterface {
public:
    MOCK_METHOD0(getchar, int());
    MOCK_METHOD4(newwin, unsigned int(int, int, int, int));
    MOCK_METHOD0(currentWindow, unsigned int());
    MOCK_METHOD0(has_colors, bool());
    MOCK_METHOD2(get_color, short(short, short));
    MOCK_METHOD1(color_on, void(short));
    MOCK_METHOD1(color_off, void(short));
    MOCK_CONST_METHOD3(mvaddch_, void(int, int, char));
};
