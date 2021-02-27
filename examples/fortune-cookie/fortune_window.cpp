#include "fortune_window.h"
#include <random>

FortuneWindow::FortuneWindow(SwearJar::Screen& screen) : Window(screen) {
    // Make the base widget align its sub-widgets horizontally
    baseWidget().alignment(SwearJar::LayoutWidget::Alignment::Horizontal);

    // Create Widgets
    baseWidget().addSpacer(); // These will take an equal amount of space
    init_widgets();
    baseWidget().addSpacer(); // either side of widgets created between them

    // Load the fortunes
    load_fortunes();
}

/// It's good practice to keep the c'tor clear and delegate the initilization
/// of the widgets to another function. In complex screens, this could even be
/// further sub-divided into more functions or re-usable widgets
void FortuneWindow::init_widgets() {
    // Within the middle column, create a vertical stack
    auto& vertical =
        baseWidget().createWidget<SwearJar::LayoutWidget>("Vertical");
    vertical.alignment(SwearJar::LayoutWidget::Alignment::Vertical);

    vertical.addSpacer(); // Again add a spacer before
    // This label will display our saying, so we keep a reference to it
    auto& label = vertical.createWidget<SwearJar::Label>("Label");
    // This label is only so the above label and the below button are separated
    // by a line It will not show any text by default
    vertical.createWidget<SwearJar::Label>("Separator");
    // This button can be clicked to show the next fortune
    auto& button = vertical.createWidget<SwearJar::Button>("Button");
    vertical.addSpacer(); // and after

    button.text(L"Get New Fortune"); // Button needs some text
    // The onPressed function will be called when the button is either clicked
    // by the mouse or Return is pressed while the button is highlighted
    button.onPressed = [&label, this](SwearJar::Button& b) {
        if (this->m_fortunes.empty()) {
            label.text(L"No wisdom for you");
        } else {
            label.text(this->get_fortune());
        }
    };
}

/// Pre-load the list of fortunes with some sayings
/// These could also be downloaded from a REST Api
/// or from a file
void FortuneWindow::load_fortunes() {
    m_fortunes = std::vector<std::wstring>{
        L"Don’t pursue happiness – create it",
        L"All things are difficult before they are easy",
        L"The real kindness comes from within you.",
        L"If you want the rainbow, you have to tolerate the rain.",
        L"He who throws mud loses ground",
        L"Big journeys begin with a single step",
        L"You learn little from success, but much from failure",
        L"A friend asks only for your time not your money",
    };
}

/// Retrieve a radom fortune
/// Here we use the pre-set list using a pseudo-random
/// number generator, but it could also come from a REST call
const std::wstring& FortuneWindow::get_fortune() {
    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<unsigned int> uniform_dist(
        0, m_fortunes.size() - 1);
    unsigned int index = uniform_dist(engine);

    return m_fortunes[index];
}
