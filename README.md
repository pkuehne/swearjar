# SwearJar

> Don't like curses? Get a swear jar!

SwearJar is a C++ library that wraps ncurses and provides extensible widgets to
build great-looking [TUIs][tui].

# Overview 🔍

Console applications are a great way to get started with a program, but as it develops, you want to add a more refined user experience than endless menus. The choice is then either Visual Studio / QT or to brave ncurses 😱.

Ncurses is itself a wrapper over the terminal ANSI escape sequences, but its far from beginner friendly. Soon most of the code will deal with the UI itself, which slows progress for those that just want to get on and write their program.

SwearJar aims to make all this easier. It doesn't just wrap the ncurses calls, but builds widgets on top of them. Widgets will be familiar to anyone who has used Visual Studio or Web programming with a JS framework such as Vue or React. SwearJar's widget model is similar to QT, though much simplified.

Widgets come in many familiar forms, such as a `Label` for displaying text or a `Button` to take an action or even a `TextBox` for entering arbitrary text. Widgets can be subclassed to add more functionality or to change the look and feel to suit your program.

SwearJar also handles things like mouse clicks, key presses and an event loop for you.

# Key Features 🔑

-   No curses calls necessary, but can be used if desired
-   Full Unicode support
-   Mouse support for clicking on buttons, dropdowns, etc.
-   Common widgets included to get started
-   Easy to add more widgets or extend existing ones.
-   Multiple overlapping windows handled automatically

# Getting started 💪

See the more [extensive guide][getting-started] available on the [Wiki][wiki].

To start, you'll need to compile the SwearJar library. Clone the repository and then run

    mkdir -p build
    cd build
    cmake ..
    make && sudo make install

That will put the library and header files in the right location on your system.

The following snippet will get you started using SwearJar, but see the Wiki for more information on usage and widgets.

    #include "swearjar.h"

    int main() {
        using namespace SwearJar;
        Screen screen(std::make_shared<SwearJar::CursesWrapper>());
        screen.init();

        // Add windows and widgets

        screen.run();
        return 0;
    }

# Roadmap 🛣️

SwearJar is still in the early stages and features are constantly being added. The interface is only semi-stable and upgrading to a new version may break existing code. After the 0.1 release, all releases will come with a migration guide.

To see what else is being considered for development, see the [Upcoming Features][upcoming] board. Features here are unprioritized and not sorted into milestones, but will give you a good idea as to where SwearJar is heading.

To see whats coming up in the next release, check the [Milestones][milestones] page in the Issues list.

# Issues & bugs 🐛

There are bugs in SwearJar. Things might also not work as you expect them to. That's normal. If this happens to you, open an issue on the issue page with the appropriate template. It will then be prioritised and potentially voted on.

If you just can't wait, feel free to contribute a Pull Request, they are always appreciated. The Contributing Guidelines give more detail on how to create a PR that will be merged quickly 👍.

# Questions ❓

See the FAQ and if your question is not answered there, please open an
[Issue][issues].

[tui]: https://en.wikipedia.org/wiki/Text-based_user_interface

[getting-started]: https://github.com/pkuehne/swearjar/wiki/Getting-Started

[wiki]: https://github.com/pkuehne/swearjar/wiki/

[upcoming]: https://github.com/pkuehne/swearjar/projects/1

[milestones]: https://github.com/pkuehne/swearjar/milestones

[issues]: https://github.com/pkuehne/swearjar/issues
