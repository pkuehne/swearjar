
add_library(swearjarbase)
target_include_directories(swearjarbase PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(swearjarbase
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/curses_interface.h
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/screen.h
    ${CMAKE_CURRENT_LIST_DIR}/screen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/panel.h
    ${CMAKE_CURRENT_LIST_DIR}/panel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widget.h
    ${CMAKE_CURRENT_LIST_DIR}/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/render_context.h
    ${CMAKE_CURRENT_LIST_DIR}/render_context.cpp
    ${CMAKE_CURRENT_LIST_DIR}/label.h
    ${CMAKE_CURRENT_LIST_DIR}/label.cpp
    ${CMAKE_CURRENT_LIST_DIR}/button.h
    ${CMAKE_CURRENT_LIST_DIR}/button.cpp
    ${CMAKE_CURRENT_LIST_DIR}/frame.h
    ${CMAKE_CURRENT_LIST_DIR}/frame.cpp
    ${CMAKE_CURRENT_LIST_DIR}/collection_widget.h
    ${CMAKE_CURRENT_LIST_DIR}/collection_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/layout_widget.h
    ${CMAKE_CURRENT_LIST_DIR}/layout_widget.cpp
    )
target_link_libraries(swearjarbase PRIVATE spdlog::spdlog)

add_library(swearjar)
target_include_directories(swearjar PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(swearjar
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/swearjar.h
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/curses_wrapper.h
    ${CMAKE_CURRENT_LIST_DIR}/curses_wrapper.cpp
    )

target_link_libraries(swearjar swearjarbase spdlog::spdlog ncurses)
