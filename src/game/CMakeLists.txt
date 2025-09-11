set(
    GAME_SRC
    GameManager.cpp
)
# 子目录
add_subdirectory(scene)
# 添加库
add_library(
    game
    ${GAME_SRC}
)
# 当前层的头文件路径
target_include_directories(
    game
    PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/scene
)
target_link_libraries(
    game
    PRIVATE
    scene
)