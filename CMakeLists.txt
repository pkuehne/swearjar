cmake_minimum_required (VERSION 3.13)
project (SwearJar
    VERSION 0.0.0
    DESCRIPTION "UI toolkit wrapper for ncurses"
    HOMEPAGE_URL "https://github.com/pkuehne/swearjar/"
    LANGUAGES CXX
    )

option(SJ_BUILD_TESTS "Whether to build the unit tests" ON)
option(SJ_BUILD_EXAMPLES "Whether to build the examples" ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses)

add_subdirectory(src)
if(SJ_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(SJ_BUILD_EXAMPLES)
    enable_testing()
    add_subdirectory(test)
endif()
