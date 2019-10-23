#include <swearjar/swearjar.h>

int main() {
    using namespace SwearJar;
    Screen screen(std::make_shared<SwearJar::CursesWrapper>());
    screen.initialize();
    screen.unhandledKeys = [&screen](KeyEvent event) { screen.quit(); };

    auto& window = screen.createWindow<Window>();
    auto& label = window.baseWidget().createWidget<Label>("Label");
    label.text(L"Hello World 👋");

    screen.run();
    return 0;
}
