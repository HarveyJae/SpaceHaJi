#include "GameManager.h"
#include "SDL.h"
GameManager::GameManager() : running_flag(false), current_scene(nullptr)
{
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
}
void GameManager::run()
{
    while (running_flag)
    {
        if (current_scene == nullptr)
        {
            clean();
            return;
        }
        SDL_Event event;
        current_scene->handle_event(&event); /* 处理场景事件*/
        current_scene->update();             /* 更新场景*/
        current_scene->render();             /* 绘制场景*/
    }
}
void GameManager::clean()
{
}
void GameManager::change_scene(Scene *scene)
{
    if (scene == nullptr)
    {
        clean();
        return;
    }
    if (current_scene != nullptr)
    {
        current_scene->clean();
        delete current_scene;
    }
    current_scene = scene;
    current_scene->init();
}