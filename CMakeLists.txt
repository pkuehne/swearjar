cmake_minimum_required (VERSION 3.13)
project (SwearJar)

set(CMAKE_CXX_STANDARD 14)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses)

add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)
