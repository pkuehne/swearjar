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
    message(STATUS "Downloading googletest repo - done")
    add_subdirectory(
        ${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}
        EXCLUDE_FROM_ALL
    )
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
    logging.test.cpp
    )

target_compile_options(unit_test PUBLIC -Wall)
if(SJ_COVERAGE)
target_compile_options(unit_test PRIVATE -fprofile-arcs)
target_compile_options(unit_test PRIVATE -ftest-coverage)
target_link_libraries(unit_test gcov)
endif()
target_link_libraries(unit_test gtest_main gmock)
target_link_libraries(unit_test swearjarbase)

add_test (
    NAME unit_test
    COMMAND unit_test --gtest_shuffle
    )

add_custom_target(tests
    DEPENDS unit_test
    COMMAND unit_test --gtest_shuffle
    )

add_custom_target(remove_gcda
    COMMAND find . -name "*.gcda" -type f -delete
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_dependencies(unit_test remove_gcda)

if(SJ_COVERAGE)
add_custom_target(coverage
    DEPENDS tests
    COMMAND gcovr -p
            -r ${CMAKE_SOURCE_DIR}/src
            --object-dir=${CMAKE_BINARY_DIR}/src
            --fail-under-line ${COVERAGE_PERCENTAGE}
            --print-summary
    )
add_custom_target(cov_xml
    COMMAND gcovr -p
    -r ${CMAKE_SOURCE_DIR}/src
    --object-dir=${CMAKE_BINARY_DIR}/src
    --xml cov.xml
    )
endif()
