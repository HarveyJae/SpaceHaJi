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
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/scene
)
target_link_libraries(
    game
    PRIVATE
    SDL2::SDL2main # 链接SDL2
    SDL2::SDL2 # 链接SDL2 
    scene
)