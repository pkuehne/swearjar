add_executable(unit_test
    widget.test.cpp
    collection-widget.test.cpp
    panel.test.cpp
    render_context.test.cpp
)

target_link_libraries(unit_test gtest_main gmock)
target_link_libraries(unit_test swearjarbase)
target_link_libraries(unit_test spdlog::spdlog)

#include(GoogleTest)
#gtest_discover_tests (unit_test)

add_test (
    NAME unit_test
    COMMAND unit_test --gtest_shuffle
)

add_custom_target(tests unit_test
    DEPENDS unit_test
    COMMAND unit_test --gtest_shuffle
)
