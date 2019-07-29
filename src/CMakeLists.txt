add_library(swearjar)

target_include_directories(swearjar PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(swearjar
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/swearjar.h
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/curses_interface.h
    ${CMAKE_CURRENT_LIST_DIR}/curses_wrapper.h
    ${CMAKE_CURRENT_LIST_DIR}/curses_wrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/app.h
    ${CMAKE_CURRENT_LIST_DIR}/app.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widget.h
    ${CMAKE_CURRENT_LIST_DIR}/widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/label.h
    ${CMAKE_CURRENT_LIST_DIR}/label.cpp
)

target_link_libraries(swearjar ncurses)