set(
    SCENE_SRC
    SceneManager.cpp
    Scene.cpp
    MainScene.cpp
    TitleScene.cpp
    EndScene.cpp
)
add_library(
    scene 
    ${SCENE_SRC}
)
target_include_directories(
    scene
    PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
    scene
    PRIVATE
    SDL2::SDL2main # 链接SDL2
    SDL2::SDL2 # 链接SDL2
)