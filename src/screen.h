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

    CursesInterface& curses() { return *m_curses; }
    template <typename T> T& createWindow();
    template <typename T>
    T& createWindow(unsigned int width, unsigned int height);
    template <typename T>
    T& createWindow(unsigned int x, unsigned int y, unsigned int width,
                    unsigned int height);
    void popWindow();
    const std::vector<std::unique_ptr<Window>>& windows() const {
        return m_windows;
    }

    void quit() { m_quit = true; }
    std::function<void(char)> unhandledKeys = [](char) {};

private:
    void handleKeys(int ch);
    void refreshWindows();

private:
    std::shared_ptr<CursesInterface> m_curses;
    std::vector<std::unique_ptr<Window>> m_windows;
    bool m_quit = false;
};

template <typename T> T& Screen::createWindow() {
    int screenHeight = 0, screenWidth = 0;
    m_curses->get_screen_size(screenHeight, screenWidth);

    return createWindow<T>(0, 0, screenWidth, screenHeight);
}

template <typename T>
T& Screen::createWindow(unsigned int width, unsigned int height) {
    int screenHeight = 0, screenWidth = 0;
    m_curses->get_screen_size(screenHeight, screenWidth);

    unsigned int x = (screenWidth / 2) - (width / 2);
    unsigned int y = (screenHeight / 2) - (height / 2);

    return createWindow<T>(x, y, width, height);
}

template <typename T>
T& Screen::createWindow(unsigned int x, unsigned int y, unsigned int width,
                        unsigned int height) {
    auto win = std::make_unique<T>(*this, x, y, width, height);
    auto& retval = *win;
    m_windows.push_back(std::move(win));
    return retval;
}
} // namespace SwearJar
