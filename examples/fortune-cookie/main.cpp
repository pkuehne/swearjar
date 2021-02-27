#include "fortune_window.h"
#include <swearjar.h>

int main() {
    SwearJar::Screen screen(new SwearJar::CursesWrapper());
    screen.initialize();

    auto& window = screen.createWindow<FortuneWindow>();

    screen.run();
    return 0;
}
