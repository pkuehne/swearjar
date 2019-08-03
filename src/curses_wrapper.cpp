#include "curses_wrapper.h"

namespace SwearJar {

CursesWrapper::CursesWrapper() {
    m_colorMap.insert({std::make_pair(-1, -1), 0});
}

void CursesWrapper::initscr() {
    ::initscr();
    m_windows.push_back(stdscr);
}

void CursesWrapper::raw() { ::raw(); }
void CursesWrapper::noecho() { ::noecho(); }
void CursesWrapper::keypad() { ::keypad(m_windows[0], 1); }
void CursesWrapper::endwin() { ::endwin(); }
bool CursesWrapper::has_colors() { return ::has_colors(); }
void CursesWrapper::start_color() { ::start_color(); }
void CursesWrapper::init_pair(short pair, short fore, short back) {
    ::init_pair(pair, fore, back);
}

short CursesWrapper::get_color(short fg, short bg) {
    auto pair = std::make_pair(fg, bg);
    auto iter = m_colorMap.find(pair);
    if (iter != m_colorMap.end()) {
        return iter->second;
    }
    ::init_pair(++m_colorMax, fg, bg);
    m_colorMap[pair] = m_colorMax;
    return m_colorMax;
}

void CursesWrapper::color_on(short pair) {
    wattron(m_windows[m_currentWindow], COLOR_PAIR(pair));
}
void CursesWrapper::color_off(short pair) {
    wattroff(m_windows[m_currentWindow], COLOR_PAIR(pair));
}

unsigned int CursesWrapper::newwin(int h, int w, int y, int x) {
    m_windows.push_back(::newwin(h, w, y, x));
    return m_windows.size() - 1;
}

void CursesWrapper::mvwprintw(int y, int x, const std::string& string) {
    ::mvwprintw(m_windows[m_currentWindow], y, x, "%s", string.c_str());
}

void CursesWrapper::mvaddch_(int y, int x, char ch) {
    mvwaddch(m_windows[m_currentWindow], y, x, ch);
}

int CursesWrapper::getchar() { return ::wgetch(stdscr); }

void CursesWrapper::refresh() { ::refresh(); }
void CursesWrapper::wrefresh() { ::wrefresh(m_windows[m_currentWindow]); }
} // namespace SwearJar