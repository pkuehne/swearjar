#include "swearjar.h"
#include <iostream>

void run() {
    SwearJar::App app;
    app.initialize();
    app.run();
}

int main() {
    std::cout << "Start!" << std::endl;

    run();

    std::cout << "Done!" << std::endl;
    return 0;
}