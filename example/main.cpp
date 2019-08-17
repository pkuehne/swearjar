#include "swearjar.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

SwearJar::Label* make_label(SwearJar::Screen& screen) {
    using namespace SwearJar;

    unsigned int x = 5;
    unsigned int y = 5;
    unsigned int w = 15;
    unsigned int h = 15;
    auto panel = screen.createPanel(x, y, w, h);
    auto label = new Label("Hello");
    label->fgColor(3);
    label->bgColor(5);
    panel->addWidget(label);

    return label;
}

SwearJar::Button* make_button(SwearJar::Screen& screen) {
    using namespace SwearJar;

    unsigned int x = 25;
    unsigned int y = 25;
    unsigned int w = 15;
    unsigned int h = 15;
    auto panel = screen.createPanel(x, y, w, h);
    auto button = new Button("Click me");
    button->fgColor(8);
    // button->bgColor(5);
    panel->addWidget(button);

    return button;
}

void run() {

    using namespace SwearJar;
    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    auto label = make_label(screen);
    auto button = make_button(screen);

    screen.unhandledKeys = [&label](char key) {
        label->text("X");
        label->centered(true);
        label->width(3);
        label->fgColor(7);
    };
    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    auto file_logger = spdlog::basic_logger_mt("basic_logger", "../logs.txt");
    spdlog::set_default_logger(file_logger);   

    spdlog::info("Starting");

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}
