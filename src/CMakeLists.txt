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

add_library(swearjarbase "${SwearJarSources}")
target_include_directories(swearjarbase PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(swearjarbase PRIVATE -Werror)
target_compile_options(swearjarbase PRIVATE -Wall)
target_compile_options(swearjarbase PRIVATE -Wextra)
target_compile_options(swearjarbase PRIVATE -Wpedantic)
target_compile_options(swearjarbase PRIVATE -g)
target_compile_options(swearjarbase PRIVATE -O2)

list (APPEND SwearJarSources
    curses_wrapper.cpp
    )
list(APPEND SwearJarHeaders
    swearjar.h
    curses_wrapper.h
    )
add_library(swearjar "${SwearJarSources}")
target_include_directories(swearjar PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_options(swearjar PRIVATE -Werror)
target_compile_options(swearjar PRIVATE -Wall)
target_compile_options(swearjar PRIVATE -Wextra)
target_compile_options(swearjar PRIVATE -Wpedantic)
target_compile_options(swearjar PRIVATE -g)
target_compile_options(swearjar PRIVATE -O2)

target_link_libraries(swearjar swearjarbase ncursesw)
set_target_properties(swearjar PROPERTIES PUBLIC_HEADER
    "${SwearJarHeaders}")

install(TARGETS swearjar
    LIBRARY
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/swearjar
    )
