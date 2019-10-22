cmake_minimum_required (VERSION 3.14)
project (SwearJar)

set(CMAKE_CXX_STANDARD 14)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Curses)

add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)
