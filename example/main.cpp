#include "frame.h"
#include "swearjar.h"
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

void make_button_label_example(SwearJar::Screen& screen) {
    using namespace SwearJar;

    // Create a Window for all our widgets
    auto& window = screen.createWindow<Window>();

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
    btnRed.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Red);
    };

    auto& btnBlue = buttonBox.createWidget<Button>("btnBlue");
    btnBlue.text("Blue");
    btnBlue.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Blue);
    };

    auto& btnYellow = buttonBox.createWidget<Button>("btnYellow");
    btnYellow.text("Yellow");
    btnYellow.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Yellow);
    };

    buttonBox.addSpacer();

    auto& btnClose = buttonBox.createWidget<Button>("btnClose");
    btnClose.text("Close");
    btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
}

// This time, instead of creating a basic Window and assigning all the widgets
// to it, we create a re-usable class that we instantiate instead
// The baseWidget() function can be used just the same to attach more widgets
// and it can then be created via the screen.createWindow() calls.
class ProgressBarExampleWindow : public SwearJar::Window {
public:
    ProgressBarExampleWindow(SwearJar::Screen& screen, unsigned int x,
                             unsigned int y, unsigned int width,
                             unsigned int height)
        : Window(screen, x, y, width, height) {
        using namespace SwearJar;

        baseWidget().alignment(LayoutWidget::Alignment::Horizontal);

        baseWidget().addSpacer();
        auto& frame = baseWidget().createWidget<Frame>("frmFrame");
        baseWidget().addSpacer();

        frame.title("Progressbar");
        frame.addSpacer();

        auto& checkbox = frame.createWidget<Checkbox>("chkBox");
        checkbox.text("Decrement");

        auto& label = frame.createWidget<Label>("lblText");
        label.text("Value");

        auto& bar = frame.createWidget<Progressbar>("pgbProgress");

        auto& btnIncr = frame.createWidget<Button>("btnIncre");
        btnIncr.text("Increment");
        btnIncr.onPressed = [&bar, &checkbox](Button& me) {
            int val = checkbox.enabled() ? -10 : 10;
            bar.value(bar.value() + val);
        };
        checkbox.onToggle = [&btnIncr](Checkbox& me) {
            btnIncr.text(me.enabled() ? "Decrement" : "Increment");
        };

        frame.addSpacer();

        auto& btnClose = frame.createWidget<Button>("btnClose");
        btnClose.text("Close");
        btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
    }
};

void make_progressbar_example(SwearJar::Screen& screen) {
    auto& window = screen.createWindow<ProgressBarExampleWindow>();
}

void make_overlapping_window(SwearJar::Screen& screen) {
    using namespace SwearJar;

    auto& window = screen.createWindow<Window>(10, 10);
    auto& baseWidget = window.baseWidget();

    baseWidget.alignment(LayoutWidget::Alignment::Vertical);
    baseWidget.bgColor(4);

    auto& lblPopup = baseWidget.createWidget<Label>("lblPopup");
    lblPopup.text("Popup");
    lblPopup.centred(true);

    baseWidget.addSpacer();

    auto& btnClose = baseWidget.createWidget<Button>("btnClose");
    btnClose.text("Close");
    btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
}

void make_example_menu(SwearJar::Screen& screen) {
    using namespace SwearJar;

    // screen.unhandledKeys = [&screen](int ch) {
    // if (ch == 'q') {
    // screen.quit();
    // }
    // };

    auto& window = screen.createWindow<Window>();
    auto& baseWidget = window.baseWidget();

    baseWidget.alignment(LayoutWidget::Alignment::Horizontal);

    baseWidget.addSpacer();
    auto& frame = baseWidget.createWidget<Frame>("frmFrame");
    baseWidget.addSpacer();

    frame.addSpacer(2);
    auto& btnLabel = frame.createWidget<Button>("btnLabel");
    auto& btnProgress = frame.createWidget<Button>("btnProgress");
    auto& btnPopup = frame.createWidget<Button>("btnPopup");
    frame.addSpacer();
    auto& btnQuit = frame.createWidget<Button>("btnQuit");
    frame.addSpacer(2);

    btnLabel.text("Labels & Buttons");
    btnLabel.onPressed = [&screen](Button&) {
        make_button_label_example(screen);
    };
    btnProgress.text("Checkbox & Progressbar");
    btnProgress.onPressed = [&screen](Button&) {
        make_progressbar_example(screen);
    };
    btnPopup.text("Popup");
    btnPopup.onPressed = [&screen](Button&) {
        make_overlapping_window(screen);
    };

    btnQuit.text("Quit");
    btnQuit.onPressed = [&screen](Button&) { screen.quit(); };
}

void run() {
    SwearJar::Screen screen(std::make_shared<SwearJar::CursesWrapper>());

    screen.initialize();
    make_example_menu(screen);
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
