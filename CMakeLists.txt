cmake_minimum_required (VERSION 3.13)
if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 0)
endif()
project (SwearJar
    VERSION 0.0.0.$ENV{TRAVIS_BUILD_NUMBER}
    DESCRIPTION "UI toolkit wrapper for ncurses"
    HOMEPAGE_URL "https://github.com/pkuehne/swearjar/"
    LANGUAGES CXX
    )

message("Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")
option(SJ_BUILD_TESTS "Whether to build the unit tests" ON)
option(SJ_BUILD_EXAMPLES "Whether to build the examples" ON)
option(SJ_COVERAGE "Whether to instrument the code for coverage data" ON)
option(SJ_LINT_COMPILATION "Whether to lint as we build with clang-tidy" OFF)
set(COVERAGE_PERCENTAGE 85 CACHE STRING "Minimum Coverage number to succeed")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses)

add_subdirectory(src)
if(SJ_BUILD_EXAMPLES AND NOT SJ_COVERAGE)
    add_subdirectory(examples)
endif()

if(SJ_BUILD_TESTS OR SJ_COVERAGE)
    enable_testing()
    add_subdirectory(test)
endif()
