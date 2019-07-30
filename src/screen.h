#pragma once

#include "curses_interface.h"
#include <memory>

namespace SwearJar {

class Screen {
public:
    Screen(std::shared_ptr<CursesInterface> curses);
    ~Screen();
    void initialize();
    void run();

private:
    std::shared_ptr<CursesInterface> m_curses;
};

} // namespace SwearJar