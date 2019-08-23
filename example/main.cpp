#include "swearjar.h"
#include "frame.h"
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

std::shared_ptr<SwearJar::Panel> make_panel(SwearJar::Screen& screen) {
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int w = 50;
    unsigned int h = 50;
    auto panel = screen.createPanel(x, y, w, h);
    return panel;
}

SwearJar::Label* make_label(std::shared_ptr<SwearJar::Panel>& panel) {
    using namespace SwearJar;

    auto label = new Label("Hello");
    label->x(5);
    label->y(0);
    label->fgColor(Color::Magenta);
    label->bgColor(Color::Black);
    panel->addWidget(label);

    return label;
}

SwearJar::Frame* make_frame(std::shared_ptr<SwearJar::Panel>& panel) {
    using namespace SwearJar;

    auto frame = new Frame("Hello");
    frame->x(30);
    frame->y(7);
    frame->width(15);
    frame->height(3);
    //frame->fgColor(Color::Magenta);
    //frame->bgColor(Color::Black);
    panel->addWidget(frame);

    return frame;
}

SwearJar::Button* make_button(std::shared_ptr<SwearJar::Panel>& panel) {
    using namespace SwearJar;

    static unsigned int y = 5;
    static unsigned int cnt = 0;
    std::string text = "Click me " + std::to_string(++cnt);
    auto button = new Button(text);
    button->x(5);
    button->y(y);
    button->gainFocus = [](Widget* w) {
        auto b = dynamic_cast<Button*>(w);
        b->text("Hit it!");
    };
    button->loseFocus = [text](Widget* w) {
        auto b = dynamic_cast<Button*>(w);
        b->text(text);
    };
    button->pressed = [&](Button* b) {
        b->fgColor(Color::Yellow);
    };
    panel->addWidget(button);

    y += 2;
    return button;
}

void run() {

    using namespace SwearJar;
    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    auto panel = make_panel(screen);
    auto label = make_label(panel);
    auto frame = make_frame(panel);
    auto button = make_button(panel);
    auto button2 = make_button(panel);
    auto button3 = make_button(panel);

    screen.unhandledKeys = [&](char key) {
        label->text("X");
        label->centered(true);
        label->width(3);
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
