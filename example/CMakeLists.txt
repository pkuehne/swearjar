add_executable(example main.cpp)
target_link_libraries(example swearjar spdlog::spdlog)

add_custom_target(examples
    COMMAND example && cat ../logs.txt
    DEPENDS example
)
