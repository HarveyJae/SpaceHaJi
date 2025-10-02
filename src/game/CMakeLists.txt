set(
    GAME_SRC
    GameManager.cpp
)
# 子目录
add_subdirectory(scene)
add_subdirectory(object)
add_subdirectory(effect)
add_subdirectory(hud)
# 添加库
add_library(
    game
    ${GAME_SRC}
)
# 当前层的头文件路径
target_include_directories(
    game
    PUBLIC
)
target_link_libraries(
    game
    PUBLIC
    scene
)
