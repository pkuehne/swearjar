cmake_minimum_required (VERSION 3.13)

# Set some basic information about the project
project (HelloWorld
	VERSION 0.0.1
	DESCRIPTION "Hello World example"
	LANGUAGES CXX
	)

# Which version of C++ to use, swearjar needs C++14
set(CMAKE_CXX_STANDARD 14)

# This makes debugging and IDEs a bit nicer
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use the FetchContent module to automatically download SwearJar
include(FetchContent)
FetchContent_Declare(
	SwearJar
	GIT_REPOSITORY https://github.com/pkuehne/swearjar.git
	GIT_TAG        development
	)

# This turns off SwearJar's unit tests and examples
option(SJ_BUILD_TESTS OFF)
option(SJ_BUILD_EXAMPLES OFF)

# Automagically make swearjar available
FetchContent_MakeAvailable(SwearJar)

# Create the executable
add_executable(hello-world main.cpp)

# Link the swearjar library (and automatically add its dependencies)
target_link_libraries(hello-world swearjar)
