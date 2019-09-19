#pragma once

#include "curses_interface.h"
#include <functional>
#include <map>
#include <memory>

namespace SwearJar {

class Window;

class Screen {
public:
    Screen(std::shared_ptr<CursesInterface> curses);
    ~Screen();
    void initialize();
    void run();
    void clearScreen();
    Window& createWindow();
    Window& createWindow(unsigned int width, unsigned int height);
    Window& createWindow(unsigned int x, unsigned int y, unsigned int width,
                         unsigned int height);
    void popWindow();

    void quit() { m_quit = true; }
    std::function<void(char)> unhandledKeys = [](char) {};

private:
    void refreshWindows();

private:
    std::shared_ptr<CursesInterface> m_curses;
    std::vector<std::unique_ptr<Window>> m_windows;
    bool m_quit = false;
};

} // namespace SwearJar
