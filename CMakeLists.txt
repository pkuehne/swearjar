cmake_minimum_required (VERSION 3.13)
project (SwearJar)

set(CMAKE_CXX_STANDARD 14)
set(CURSES_NEED_NCURSES TRUE)

find_package(Curses)

set(INSTALL_GTEST OFF CACHE BOOL "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" FORCE)
add_subdirectory(third-party/googletest)

add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(test)
