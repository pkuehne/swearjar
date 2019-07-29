add_library(swearjar)

target_include_directories(swearjar PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(swearjar
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/widget.h
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/widget.cpp
)

target_link_libraries(swearjar ncurses)