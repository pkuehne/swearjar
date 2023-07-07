#include "screen.h"
#include "logging.h"
#include "window.h"
#include <iostream>

namespace SwearJar {

Screen::Screen(std::shared_ptr<CursesInterface>&& curses) : m_curses(curses) {
    unhandledKeys = [this](const KeyEvent& /* e */) { quit(); };
    screenResized = []() {};

    LOG_FORCE << "Screen initialized for version " << VERSION << LOG_END;
}

Screen::Screen(CursesInterface* curses)
    : Screen(std::shared_ptr<CursesInterface>(curses)) {
}

Screen::~Screen() {
    m_curses->endwin();
}

void Screen::initialize() {
    m_curses->initscr();
    m_curses->raw();
    m_curses->noecho();
    m_curses->nodelay(true);
    m_curses->keypad();
    if (m_curses->has_colors()) {
        m_curses->start_color();
    }
    m_curses->enable_mouse();
}

void Screen::run() {
    m_curses->nodelay(false); // We want to wait for keypresses
    while (!m_quit) {
        update();
    }
}

void Screen::update() {
    refreshWindows();
    handleInput();
}

CursesInterface& Screen::curses() {
    return *m_curses;
}

void Screen::popWindow() {
    if (m_windows.empty()) {
        return;
    }
    m_windows.pop_back();
}

void Screen::refreshWindows() {
    for (auto& window : m_windows) {
        window->refresh();
    }
    m_curses->refresh();
}

void Screen::resizeWindows() {
    LOG_INFO << "Resizing windows" << LOG_END;
    for (auto& window : m_windows) {
        window->resize();
    }
    m_curses->refresh();
}

const std::vector<std::unique_ptr<Window>>& Screen::windows() const {
    return m_windows;
}

void Screen::quit() {
    m_quit = true;
}

bool Screen::shouldQuit() {
    return m_quit;
}

void Screen::handleInput() {
    int ch = m_curses->getchar();
    switch (ch) {
        case KEY_MOUSE: {
            MouseEvent event = m_curses->mouse_event();
            handleMouse(event);
            break;
        }
        case KEY_RESIZE: {
            resizeWindows();
            screenResized();
            break;
        }
        default: {
            KeyEvent event;
            event.key = ch;
            handleKeys(event);
            break;
        }
    }
}

void Screen::handleKeys(const KeyEvent& event) {
    LOG_DEBUG << "Handling key " << event.key << LOG_END;
    if (event.key == KEY_TAB) {
        (*m_windows.rbegin())->baseWidget().moveFocusForward();
        return;
    }
    bool handled = (*m_windows.rbegin())->baseWidget().handleKeyPress(event);
    if (!handled) {
        unhandledKeys(event);
    }
}

void Screen::handleMouse(const MouseEvent& event) {
    LOG_DEBUG << "Device: " << event.device << " x=" << event.x
              << " y=" << event.y << " l=" << event.leftClicked
              << " r=" << event.rightClicked << LOG_END;
    if (!event.leftClicked) {
        LOG_DEBUG << "Not a left-click" << LOG_END;
        return;
    }
    auto& topWin = *(*m_windows.rbegin());
    if (topWin.contains(event.x, event.y)) {
        // Convert from scren coordinates to window coordinates
        MouseEvent l_event(event);
        l_event.x -= topWin.x() - 1;
        l_event.y -= topWin.y() - 1;
        LOG_DEBUG << "handling button click @ (" << l_event.x << ", "
                  << l_event.y << ")" << LOG_END;
        topWin.baseWidget().handleMouseClick(l_event);
    }
}
} // namespace SwearJar
