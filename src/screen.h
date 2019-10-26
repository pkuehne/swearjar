#pragma once

#include "curses_interface.h"
#include <functional>
#include <memory>
#include <vector>

namespace SwearJar {

class Window;

class Screen {
public:
    explicit Screen(std::shared_ptr<CursesInterface>&& curses);
    ~Screen();
    void initialize();
    void run();

    CursesInterface& curses() {
        return *m_curses;
    }
    template <typename T> T& createWindow();
    void popWindow();
    const std::vector<std::unique_ptr<Window>>& windows() const {
        return m_windows;
    }

    void quit() {
        m_quit = true;
    }
    std::function<void(const KeyEvent&)> unhandledKeys = [](const KeyEvent&) {};
    std::function<void()> screenResized = []() {};

private:
    void handleKeys(const KeyEvent& event);
    void handleMouse(const MouseEvent& event);
    void refreshWindows();
    void resizeWindows();

private:
    std::shared_ptr<CursesInterface> m_curses;
    std::vector<std::unique_ptr<Window>> m_windows;
    bool m_quit = false;
};

template <typename T> T& Screen::createWindow() {
    auto win = std::make_unique<T>(*this);
    auto& retval = *win;
    m_windows.push_back(std::move(win));
    return retval;
}

} // namespace SwearJar
