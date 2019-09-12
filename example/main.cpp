#include "frame.h"
#include "swearjar.h"
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

void make_button_label_example(SwearJar::Screen& screen) {
    using namespace SwearJar;

    auto panel = screen.createPanel();
    auto baseWidget = panel->baseWidget();
    baseWidget->alignment(LayoutWidget::Alignment::Horizontal);

    baseWidget->addSpacer();
    auto frame = panel->createWidget<Frame>("frmFrame");
    baseWidget->addSpacer();

    frame->title("Button Example");
    frame->alignment(LayoutWidget::Alignment::Vertical);
    frame->addSpacer();

    auto lblDisplay = frame->createWidget<Label>("lblDisplay");
    lblDisplay->centred(true);
    lblDisplay->text("This is a label");
    lblDisplay->fgColor(Color::Magenta);
    lblDisplay->bgColor(Color::Black);

    frame->addSpacer();

    auto buttonWrapper = frame->createWidget<LayoutWidget>("margin");
    buttonWrapper->alignment(LayoutWidget::Alignment::Horizontal);
    buttonWrapper->addSpacer();
    auto buttonBox = buttonWrapper->createWidget<LayoutWidget>("buttons");
    buttonWrapper->addSpacer();

    buttonBox->alignment(LayoutWidget::Alignment::Vertical);

    auto btnRed = buttonBox->createWidget<Button>("btnRed");
    btnRed->text("Red");
    btnRed->pressed = [lblDisplay](Button*) {
        lblDisplay->fgColor(Color::Red);
    };

    auto btnBlue = buttonBox->createWidget<Button>("btnBlue");
    btnBlue->text("Blue");
    btnBlue->pressed = [lblDisplay](Button*) {
        lblDisplay->fgColor(Color::Blue);
    };

    auto btnYellow = buttonBox->createWidget<Button>("btnYellow");
    btnYellow->text("Yellow");
    btnYellow->pressed = [lblDisplay](Button*) {
        lblDisplay->fgColor(Color::Yellow);
    };

    frame->addSpacer(2);
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
    button->pressed = [&](Button* b) { b->fgColor(Color::Yellow); };
    panel->addWidget(button);

    y += 2;
    return button;
}

void run() {
    using namespace SwearJar;
    Screen screen(std::make_shared<CursesWrapper>());
    screen.initialize();

    make_button_label_example(screen);
    // auto panel = make_panel(screen);
    // auto label = make_label(panel);
    // auto frame = make_frame(panel);
    // auto button = make_button(panel);
    // auto button2 = make_button(panel);
    // auto button3 = make_button(panel);

    // screen.unhandledKeys = [&](char key) {
    // label->text("X");
    // label->centered(true);
    // label->width(3);
    //};
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
