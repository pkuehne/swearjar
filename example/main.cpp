#include "swearjar.h"
#include <iostream>

void run() {
    using namespace SwearJar;

    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    auto panel = screen.createPanel(15, 15, 5, 5);
    auto label = new Label("Hello");
    label->fgColor(3);
    label->bgColor(5);
    panel->addWidget(label);

    screen.unhandledKeys = [&label](char key) {
        label->text("Bye");
        label->x(label->x() + 1);
        label->fgColor(122);
    };
    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}