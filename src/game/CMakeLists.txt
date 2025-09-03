# scene库路径
add_subdirectory(scene)
set(
    GAME_SRC
    GameManager.cpp
)
add_library(
    game
    ${GAME_SRC}
)
target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
    game
    PRIVATE scene
)