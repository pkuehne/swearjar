#include "frame.h"
#include "logging.h"
#include "swearjar.h"
#include <iostream>

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
    frame.title(L" Button Example ");
    frame.addSpacer();

    // Add a centred label with some magenta on black text
    auto& lblDisplay = frame.createWidget<Label>("lblDisplay");
    lblDisplay.centred(true);
    lblDisplay.text(L"This is a label");
    lblDisplay.fgColor(Color::Magenta);
    lblDisplay.bgColor(Color::Black);

    // The order in which widgets and spacers are created matters!
    frame.addSpacer();
    auto& buttonWrapper = frame.createWidget<LayoutWidget>("marginBox");
    frame.addSpacer(2);

    // Wrap the buttons in a LayoutWidget so we can give them extra margin on
    // the sides inside the Frame
    // Then add the buttons inside a vertical LayoutWidget so they stack one on
    // top of the other
    buttonWrapper.alignment(LayoutWidget::Alignment::Horizontal);
    buttonWrapper.addSpacer();
    auto& buttonBox = buttonWrapper.createWidget<LayoutWidget>("buttonBox");
    buttonBox.alignment(LayoutWidget::Alignment::Vertical);
    buttonWrapper.addSpacer();

    // The `pressed` property is called whenever the button is clicked either
    // by keyboard or mouse
    auto& btnRed = buttonBox.createWidget<Button>("btnRed");
    btnRed.text(L"Red");
    btnRed.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Red);
    };

    auto& btnBlue = buttonBox.createWidget<Button>("btnBlue");
    btnBlue.text(L"Blue");
    btnBlue.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Blue);
    };

    auto& btnYellow = buttonBox.createWidget<Button>("btnYellow");
    btnYellow.text(L"Yellow");
    btnYellow.onPressed = [&lblDisplay](Button&) {
        lblDisplay.fgColor(Color::Yellow);
    };

    // buttonBox.addSpacer();

    auto& btnClose = frame.createWidget<Button>("btnClose");
    btnClose.text(L"Close");
    btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
}

// This time, instead of creating a basic Window and assigning all the widgets
// to it, we create a re-usable class that we instantiate instead
// The baseWidget() function can be used just the same to attach more widgets
// and it can then be created via the screen.createWindow() calls.
class ProgressBarExampleWindow : public SwearJar::Window {
public:
    ProgressBarExampleWindow(SwearJar::Screen& screen) : Window(screen) {
        using namespace SwearJar;

        baseWidget().alignment(LayoutWidget::Alignment::Horizontal);

        baseWidget().addSpacer();
        auto& frame = baseWidget().createWidget<Frame>("frmFrame");
        baseWidget().addSpacer();

        frame.title(L"Progressbar");
        frame.addSpacer();

        auto& checkbox = frame.createWidget<Checkbox>("chkBox");
        checkbox.text(L"Decrement");

        auto& label = frame.createWidget<Label>("lblText");
        label.text(L"Value");

        auto& bar = frame.createWidget<Progressbar>("pgbProgress");

        auto& btnIncr = frame.createWidget<Button>("btnIncre");
        btnIncr.text(L"Increment");
        btnIncr.onPressed = [&bar, &checkbox](Button& me) {
            int val = checkbox.enabled() ? -10 : 10;
            bar.value(bar.value() + val);
        };
        checkbox.onToggle = [&btnIncr](Checkbox& me) {
            btnIncr.text(me.enabled() ? L"Decrement" : L"Increment");
        };

        frame.addSpacer();

        auto& btnClose = frame.createWidget<Button>("btnClose");
        btnClose.text(L"Close");
        btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
    }
};

void make_overlapping_window(SwearJar::Screen& screen) {
    using namespace SwearJar;

    auto& window = screen.createWindow<Window>();
    window.setWindowStyleFractional(30, 30);

    auto& baseWidget = window.baseWidget();

    baseWidget.alignment(LayoutWidget::Alignment::Vertical);
    baseWidget.bgColor(4);

    auto& lblPopup = baseWidget.createWidget<Label>("lblPopup");
    lblPopup.text(L"Popup");
    lblPopup.centred(true);

    baseWidget.addSpacer();

    auto& btnClose = baseWidget.createWidget<Button>("btnClose");
    btnClose.text(L"Close");
    btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
}

class ListExampleWindow : public SwearJar::Window {
public:
    ListExampleWindow(SwearJar::Screen& screen) : Window(screen) {
        using namespace SwearJar;

        baseWidget().alignment(LayoutWidget::Alignment::Horizontal);

        baseWidget().addSpacer();
        auto& frame = baseWidget().createWidget<Frame>("frmFrame");
        baseWidget().addSpacer();

        frame.title(L"List");
        frame.addSpacer();

        auto& buttonOne = frame.createWidget<RadioButton>("btnOne");
        buttonOne.text(L"Button 1");
        auto& buttonTwo = frame.createWidget<RadioButton>("btnTwo");
        buttonTwo.text(L"Button 2");
        auto& buttonThree = frame.createWidget<RadioButton>("btnThree");
        buttonThree.text(L"Button 3");

        m_buttonGroup.add(&buttonOne);
        m_buttonGroup.add(&buttonTwo);
        m_buttonGroup.add(&buttonThree);

        frame.addSpacer();
        auto& list = frame.createWidget<List>("lstExample");
        list.addItem(L"Item 1");
        list.addItem(L"Item 2");
        list.addItem(L"Item 3");
        list.addItem(L"Item 4");
        list.addItem(L"Item 5");
        list.growthFactor(0);
        list.minHeight(3);

        frame.addSpacer();
        auto& btnClose = frame.createWidget<Button>("btnClose");
        btnClose.text(L"Close");
        btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
    }

private:
    SwearJar::RadioButtonGroup m_buttonGroup;
};

class TextEntryExampleWindow : public SwearJar::Window {
public:
    TextEntryExampleWindow(SwearJar::Screen& screen) : Window(screen) {
        using namespace SwearJar;

        baseWidget().alignment(LayoutWidget::Alignment::Horizontal);

        baseWidget().addSpacer();
        auto& frame = baseWidget().createWidget<Frame>("frmFrame");
        baseWidget().addSpacer();

        frame.title(L"TextEntry");
        frame.addSpacer();

        auto& lblText = frame.createWidget<Label>("lblText");
        lblText.text(L"Type your name: ");

        frame.addSpacer();

        auto& txtEntry = frame.createWidget<TextEntry>("txtEntry");
        txtEntry.onTextChanged = [&lblText](TextEntry& e) {
            if (e.text().size()) {
                lblText.text(L"Hit Enter when done!");
            } else {
                lblText.text(L"Type your name: ");
            }
        };
        txtEntry.onSubmit = [&lblText](TextEntry& e) {
            if (e.text().size()) {
                lblText.text(L"Hello, " + e.text());
            }
        };

        frame.addSpacer();
        auto& btnClose = frame.createWidget<Button>("btnClose");
        btnClose.text(L"Close");
        btnClose.onPressed = [&screen](Button&) { screen.popWindow(); };
    }
};
void make_example_menu(SwearJar::Screen& screen) {
    using namespace SwearJar;

    screen.unhandledKeys = [&screen](KeyEvent e) {
        if (e.key == 'q') {
            screen.quit();
        }
    };

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
    auto& btnList = frame.createWidget<Button>("btnList");
    auto& btnEntry = frame.createWidget<Button>("btnEntry");
    frame.addSpacer();
    auto& btnQuit = frame.createWidget<Button>("btnQuit");
    frame.addSpacer(2);

    btnLabel.text(L"Labels € Buttons");
    btnLabel.onPressed = [&screen](Button&) {
        make_button_label_example(screen);
    };
    btnProgress.text(L"Checkbox & Progressbar");
    btnProgress.onPressed = [&screen](Button&) {
        screen.createWindow<ProgressBarExampleWindow>();
    };
    btnPopup.text(L"Popup");
    btnPopup.onPressed = [&screen](Button&) {
        make_overlapping_window(screen);
    };
    btnList.text(L"List");
    btnList.onPressed = [&screen](Button&) {
        screen.createWindow<ListExampleWindow>();
    };
    btnEntry.text(L"TextEntry");
    btnEntry.onPressed = [&screen](Button&) {
        screen.createWindow<TextEntryExampleWindow>();
    };

    btnQuit.text(L"Quit");
    btnQuit.onPressed = [&screen](Button&) { screen.quit(); };
}

void run() {
    SwearJar::Screen screen(new SwearJar::CursesWrapper());

    screen.initialize();
    SwearJar::LogManager::get()->threshold(SwearJar::LogLevel::Info);
    make_example_menu(screen);
    screen.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}
