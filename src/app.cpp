#include "app.h"
#include <ncurses.h>

namespace SwearJar {

App::App() {
    //
}

App::~App() {
    endwin();
}

void App::initialize() {
    initscr();              // Start curses mode
	raw();                  // Line buffering disabled
	keypad(stdscr, TRUE);   // We get F1, F2 etc...
	noecho();               // Don't echo() while we do getch
}

void App::run() {
    mvprintw(5, 5, "Hello");
    int ch = getch();
}

} // close namespace