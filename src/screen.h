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

    /// Call this with `new CursesWrapper()`. Screen will take ownership of the
    /// pointer.
    explicit Screen(CursesInterface* curses);

    ~Screen();

    /// Sets up the underlying drawing system. Call this when you are ready to
    /// hand over control of the screen to SwearJar
    void initialize();

    // Hand over control to SwearJar
    void run();

    /// Get access to the underlying Curses wrapper
    CursesInterface& curses() {
        return *m_curses;
    }

    /// Create a new window and make it topmost within the application
    template <typename T> T& createWindow();

    /// Remove the top window
    void popWindow();

    /// Get a list of all windows the Screen is currently managing
    const std::vector<std::unique_ptr<Window>>& windows() const {
        return m_windows;
    }

    /// End control of the screen
    void quit() {
        m_quit = true;
    }

    /// This function will be called for any keyboard keys that are not handled
    /// by SwearJar directly. Will by default quit the application when any key
    /// is pressed
    std::function<void(const KeyEvent&)> unhandledKeys =
        [this](const KeyEvent& /* e */) { quit(); };

    /// This function will be called whenever the screen is resized. SwearJar
    /// will re-align widgets automatically
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
