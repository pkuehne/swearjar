#include "curses_wrapper.h"
#include "logging.h"
#include <csignal>

namespace SwearJar {

CursesWrapper::CursesWrapper() {
    LOG_DEBUG << "CW: initializing CursesWrapper" << LOG_END;
    m_colorMap.insert({std::make_pair(-1, -1), 0});
}

void CursesWrapper::initscr() {
    setlocale(LC_CTYPE, "");
    ::initscr();
    m_windows.push_back(stdscr);
    ::color_set(get_color(7, 0), 0);
    ::curs_set(0);
    ::refresh();
    setupResizeHandler();
}

void CursesWrapper::raw() {
    ::raw();
}
void CursesWrapper::noecho() {
    ::noecho();
}
void CursesWrapper::keypad() {
    ::keypad(m_windows[0], true);
}
void CursesWrapper::endwin() {
    ::endwin();
}
bool CursesWrapper::has_colors() {
    return ::has_colors();
}
void CursesWrapper::start_color() {
    ::start_color();
}
void CursesWrapper::init_pair(short pair, short fore, short back) {
    ::init_pair(pair, fore, back);
}
void CursesWrapper::enable_mouse() {
    mousemask(BUTTON1_CLICKED | BUTTON2_CLICKED | REPORT_MOUSE_POSITION,
              nullptr);
}
MouseEvent CursesWrapper::mouse_event() {
    MouseEvent event;

    MEVENT mouse;
    if (getmouse(&mouse) != OK) {
        return event;
    }

    event.device = mouse.id;
    event.x = mouse.x;
    event.y = mouse.y;
    event.leftClicked = ((mouse.bstate & BUTTON1_CLICKED) != 0);
    event.rightClicked = ((mouse.bstate & BUTTON2_CLICKED) != 0);
    return event;
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

void CursesWrapper::reverse_on() {
    wattron(m_windows[m_currentWindow], A_REVERSE);
}

void CursesWrapper::reverse_off() {
    wattroff(m_windows[m_currentWindow], A_REVERSE);
}

void CursesWrapper::blink_on() {
    wattron(m_windows[m_currentWindow], A_BLINK);
}

void CursesWrapper::blink_off() {
    wattroff(m_windows[m_currentWindow], A_BLINK);
}

void CursesWrapper::wbkgd(short pair) {
    ::wbkgd(m_windows[m_currentWindow], COLOR_PAIR(pair));
    ::touchwin(m_windows[m_currentWindow]);
}

void CursesWrapper::get_screen_size(int* height, int* width) {
    getmaxyx(stdscr, *height, *width);
}

unsigned int CursesWrapper::newwin(int h, int w, int y, int x) {
    m_windows.push_back(::newwin(h, w, y, x));
    return m_windows.size() - 1;
}

void CursesWrapper::wresize(int h, int w) {
    ::wresize(m_windows[m_currentWindow], h, w);
}

void CursesWrapper::mvwin(int y, int x) {
    ::mvwin(m_windows[m_currentWindow], y, x);
}

void CursesWrapper::mvwprint(int y, int x, const std::string& string) const {
    mvwaddstr(m_windows[m_currentWindow], y, x, string.c_str());
}

void CursesWrapper::mvwprintw(int y, int x, const std::wstring& string) const {
    mvwaddwstr(m_windows[m_currentWindow], y, x, string.c_str());
}

void CursesWrapper::mvaddch_(int y, int x, char ch) const {
    mvwaddch(m_windows[m_currentWindow], y, x, ch);
}

void CursesWrapper::mvaddwch_(int y, int x, wchar_t ch) const {
    const cchar_t out = {A_NORMAL, {ch},0};
    mvwadd_wch(m_windows[m_currentWindow], y, x, &out);
}

int CursesWrapper::getchar() {
    return ::wgetch(stdscr);
}

void CursesWrapper::refresh() {
    ::refresh();
}
void CursesWrapper::wrefresh() {
    ::wrefresh(m_windows[m_currentWindow]);
}
void CursesWrapper::touchwin_() {
    ::touchwin(m_windows[m_currentWindow]);
}

void handle_winch(int /* x */) {
    endwin();
    refresh();
    clear();
    refresh();
    ungetch(KEY_RESIZE);
}

void CursesWrapper::setupResizeHandler() {
    struct sigaction sa {};
    sa.sa_handler = handle_winch;
    sigaction(SIGWINCH, &sa, nullptr);
}

} // namespace SwearJar
