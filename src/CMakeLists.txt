add_compile_definitions(VERSION="${PROJECT_VERSION}")

list (APPEND SwearJarSources
    screen.cpp
    window.cpp
    widget.cpp
    render_context.cpp
    label.cpp
    button.cpp
    frame.cpp
    progressbar.cpp
    collection_widget.cpp
    layout_widget.cpp
    checkbox.cpp
    list.cpp
    radio_button.cpp
    text_entry.cpp
    logging.cpp
    )
list(APPEND SwearJarHeaders
    curses_interface.h
    screen.h
    window.h
    widget.h
    render_context.h
    label.h
    button.h
    frame.h
    progressbar.h
    collection_widget.h
    layout_widget.h
    checkbox.h
    list.h
    radio_button.h
    text_entry.h
    )

if (SJ_LINT_COMPILATION)
set(CMAKE_CXX_CLANG_TIDY clang-tidy; -format-style=file)
endif()

# Create an object library that is not linked, but serves as a collection of
# objects for other libraries
add_library(swearjarobjects OBJECT "${SwearJarSources}")
if(NOT SJ_COVERAGE)
target_compile_options(swearjarobjects PRIVATE -Werror)
target_compile_options(swearjarobjects PRIVATE -Wall)
target_compile_options(swearjarobjects PRIVATE -Wextra)
target_compile_options(swearjarobjects PRIVATE -Wpedantic)
target_compile_options(swearjarobjects PRIVATE -g)
target_compile_options(swearjarobjects PRIVATE -O2)
else()
target_compile_options(swearjarobjects PRIVATE -fprofile-arcs)
target_compile_options(swearjarobjects PRIVATE -ftest-coverage)
endif()

# Build swearjarbase without a concrete CursesInterface implementation
add_library(swearjarbase $<TARGET_OBJECTS:swearjarobjects>)
target_include_directories(swearjarbase PUBLIC ${CMAKE_CURRENT_LIST_DIR})

list(APPEND SwearJarHeaders
    swearjar.h
    curses_wrapper.h
    )
# Build swearjar with CursesWrapper and all swearjar objects from the base
add_library(swearjar curses_wrapper.cpp $<TARGET_OBJECTS:swearjarobjects>)
target_include_directories(swearjar PUBLIC ${CMAKE_CURRENT_LIST_DIR})
if(NOT SJ_COVERAGE)
target_compile_options(swearjar PRIVATE -Werror)
target_compile_options(swearjar PRIVATE -Wall)
target_compile_options(swearjar PRIVATE -Wextra)
target_compile_options(swearjar PRIVATE -Wpedantic)
target_compile_options(swearjar PRIVATE -g)
target_compile_options(swearjar PRIVATE -O2)
else()
target_compile_options(swearjarbase PRIVATE -fprofile-arcs)
target_compile_options(swearjarbase PRIVATE -ftest-coverage)
endif()

target_link_libraries(swearjar swearjarbase ncursesw)
set_target_properties(swearjar PROPERTIES PUBLIC_HEADER
    "${SwearJarHeaders}")

install(TARGETS swearjar
    LIBRARY
        DESTINATION lib
    PUBLIC_HEADER
        DESTINATION include/swearjar
    )
