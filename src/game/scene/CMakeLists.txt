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
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)