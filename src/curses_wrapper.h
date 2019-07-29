#pragma once

#include "curses_interface.h"

namespace SwearJar {

class CursesWrapper : public CursesInterface {
public:
    void initscr();
    void raw();
    void noecho();
    void keypad();

    int getchar();
};

} // namespace SwearJar