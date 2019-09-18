#include "frame.h"
#include "swearjar.h"
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

void make_button_label_example(SwearJar::Screen& screen) {
    using namespace SwearJar;

    // Create a Window for all our widgets
    auto& window = screen.createWindow();

    // Grab the base widget and make layout its children horizontally
    auto& baseWidget = window.baseWidget();
    baseWidget.alignment(LayoutWidget::Alignment::Horizontal);

    // Create a new Frame widget and put spacers either side for automatic
    // margin
    baseWidget.addSpacer();
    auto& frame = baseWidget.createWidget<Frame>("frmFrame");
    baseWidget.addSpacer();

    // The Frame has a Layout itself and by default its vertical
    frame.title(" Button Example ");
    frame.addSpacer();

    // Add a centred label with some magenta on black text
    auto& lblDisplay = frame.createWidget<Label>("lblDisplay");
    lblDisplay.centred(true);
    lblDisplay.text("This is a label");
    lblDisplay.fgColor(Color::Magenta);
    lblDisplay.bgColor(Color::Black);

    // The order in which widgets and spacers are created matters!
    frame.addSpacer();
    auto& buttonWrapper = frame.createWidget<LayoutWidget>("margin");
    frame.addSpacer(2);

    // Wrap the buttons in a LayoutWidget so we can give them extra margin on
    // the sides inside the Frame
    // Then add the buttons inside a vertical LayoutWidget so they stack one on
    // top of the other
    buttonWrapper.alignment(LayoutWidget::Alignment::Horizontal);
    buttonWrapper.addSpacer();
    auto& buttonBox = buttonWrapper.createWidget<LayoutWidget>("buttons");
    buttonBox.alignment(LayoutWidget::Alignment::Vertical);
    buttonWrapper.addSpacer();

    // The `pressed` property is called when ever the button is clicked either
    // by keyboard or mouse
    auto& btnRed = buttonBox.createWidget<Button>("btnRed");
    btnRed.text("Red");
    btnRed.pressed = [&lblDisplay](Button&) { lblDisplay.fgColor(Color::Red); };

    auto& btnBlue = buttonBox.createWidget<Button>("btnBlue");
    btnBlue.text("Blue");
    btnBlue.pressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Blue);
    };

    auto& btnYellow = buttonBox.createWidget<Button>("btnYellow");
    btnYellow.text("Yellow");
    btnYellow.pressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Yellow);
    };
}

void make_progressbar_example(SwearJar::Screen& screen) {
    using namespace SwearJar;

    // Create a Window for all our widgets
    auto& window = screen.createWindow();

    // Grab the base widget and make layout its children horizontally
    auto& baseWidget = window.baseWidget();
    baseWidget.alignment(LayoutWidget::Alignment::Horizontal);

    baseWidget.addSpacer();
    auto& frame = baseWidget.createWidget<Frame>("frmFrame");
    baseWidget.addSpacer();

    frame.title("Progressbar");
    frame.addSpacer();

    auto& checkbox = frame.createWidget<Checkbox>("chkBox");
    checkbox.text("Decrement");

    auto& label = frame.createWidget<Label>("lblText");
    label.text("Value");

    auto& bar = frame.createWidget<Progressbar>("pgbProgress");

    auto& btnIncr = frame.createWidget<Button>("btnIncre");
    btnIncr.text("Increment");
    btnIncr.pressed = [&bar, &checkbox](Button& me) {
        int val = checkbox.enabled() ? -10 : 10;
        bar.value(bar.value() + val);
    };
    checkbox.onToggle = [&btnIncr](Checkbox& me) {
        btnIncr.text(me.enabled() ? "Decrement" : "Increment");
    };

    frame.addSpacer();
}

void run() {
    SwearJar::Screen screen(std::make_shared<SwearJar::CursesWrapper>());
    screen.initialize();

    // make_button_label_example(screen);
    make_progressbar_example(screen);
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
