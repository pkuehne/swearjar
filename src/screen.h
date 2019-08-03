#pragma once

#include "curses_interface.h"
#include <functional>
#include <map>
#include <memory>

namespace SwearJar {

class Panel;

class Screen {
public:
    Screen(std::shared_ptr<CursesInterface> curses);
    ~Screen();
    void initialize();
    void run();
    void clearScreen();
    std::shared_ptr<Panel> createPanel(unsigned int height, unsigned int width,
                                       unsigned int y, unsigned int x);
    void quit() { m_quit = true; }
    std::function<void(char)> unhandledKeys = [](char) {};

private:
    void refreshDirtyWidgets();

private:
    std::shared_ptr<CursesInterface> m_curses;
    std::map<unsigned int, std::shared_ptr<Panel>> m_panels;
    bool m_quit = false;
};

} // namespace SwearJar