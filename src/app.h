#pragma once

#include "curses_interface.h"
#include <memory>

namespace SwearJar {

class App {
public:
    App(std::shared_ptr<CursesInterface> curses);
    ~App();
    void initialize();
    void run();

private:
    std::shared_ptr<CursesInterface> m_curses;
};

} // namespace SwearJar