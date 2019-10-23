include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    message(STATUS "Downloading googletest repo")
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    message(STATUS "Downloading googletest repo - done")
endif()

add_executable(unit_test
    screen.test.cpp
    widget.test.cpp
    collection-widget.test.cpp
    window.test.cpp
    render_context.test.cpp
    layout_widget.test.cpp
    button.test.cpp
    progressbar.test.cpp
    list.test.cpp
    checkbox.test.cpp
    radio_button.test.cpp
    text_entry.test.cpp
    frame.test.cpp
    label.test.cpp
    )

target_compile_options(unit_test PUBLIC -Wall)
target_link_libraries(unit_test gtest_main gmock)
target_link_libraries(unit_test swearjarbase)

add_test (
    NAME unit_test
    COMMAND unit_test --gtest_shuffle
    )

add_custom_target(tests unit_test
    DEPENDS unit_test
    COMMAND unit_test --gtest_shuffle
    )
