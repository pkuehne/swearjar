#include "curses_wrapper.h"

namespace SwearJar {

void CursesWrapper::initscr() {
    ::initscr();
    m_windows.push_back(stdscr);
}
void CursesWrapper::raw() { ::raw(); }
void CursesWrapper::noecho() { ::noecho(); }
void CursesWrapper::keypad() { ::keypad(m_windows[0], 1); }
void CursesWrapper::endwin() { ::endwin(); }

unsigned int CursesWrapper::newwin(int h, int w, int y, int x) {
    m_windows.push_back(::newwin(h, w, y, x));
    return m_windows.size() - 1;
}

void CursesWrapper::mvwprintw(int y, int x, const std::string& string) {
    ::mvwprintw(m_windows[m_currentWindow], y, x, "%s", string.c_str());
}

int CursesWrapper::getchar() { return ::wgetch(stdscr); }

void CursesWrapper::refresh() { ::refresh(); }
void CursesWrapper::wrefresh() { ::wrefresh(m_windows[m_currentWindow]); }
} // namespace SwearJar