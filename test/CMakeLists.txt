add_executable(unit_test
    widget.test.cpp
    panel.test.cpp
)

target_link_libraries(unit_test gtest_main gmock)
target_link_libraries(unit_test swearjarbase)

include(GoogleTest)
gtest_discover_tests (unit_test)