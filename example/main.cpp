#include "curses_wrapper.h"
#include "swearjar.h"
#include <iostream>

void run() {
    using namespace SwearJar;

    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    auto panel = screen.createPanel(10, 20, 5, 5);
    panel->addWidget(new Label("Hello"));

    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}