#include "curses_wrapper.h"
#include "swearjar.h"
#include <iostream>

void run() {
    SwearJar::Screen screen(std::make_shared<SwearJar::CursesWrapper>());
    screen.initialize();
    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}