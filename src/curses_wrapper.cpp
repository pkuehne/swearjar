#include "curses_wrapper.h"
#include <ncurses.h>

namespace SwearJar {

void CursesWrapper::initscr() { ::initscr(); }
void CursesWrapper::raw() { ::raw(); }
void CursesWrapper::noecho() { ::noecho(); }
void CursesWrapper::keypad() { ::keypad(stdscr, 1); }

int CursesWrapper::getchar() { return wgetch(stdscr); }

} // namespace SwearJar