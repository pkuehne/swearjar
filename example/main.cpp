#include "swearjar.h"
#include <iostream>

void run() {
    using namespace SwearJar;

    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    auto panel = screen.createPanel(5, 5, 5, 5);
    auto label = new Label("Hello");
    panel->addWidget(label);

    screen.unhandledKeys = [&label](char key) { label->text("Bye"); };
    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}