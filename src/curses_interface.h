#pragma once

namespace SwearJar {

class CursesInterface {
public:
    virtual void initscr() = 0;
    virtual void raw() = 0;
    virtual void noecho() = 0;
    virtual void keypad() = 0;
    virtual void endwin() = 0;

    virtual int getchar() = 0;
};

} // namespace SwearJar