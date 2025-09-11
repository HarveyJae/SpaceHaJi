#include "GameManager.h"
#include <iostream>
#include "MainScene.h"
#include "SDL.h"
GameManager::GameManager() : running_flag(false), current_scene(nullptr)
{
}

GameManager::~GameManager()
{
    clean();
}

void GameManager::init()
{
    /* SDL初始化*/
    int retval = 0;
    retval = SDL_Init(SDL_INIT_EVERYTHING);
    if (retval != 0)
    {
        std::cout << "SDL Init failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 创建窗口*/
    window = SDL_CreateWindow(SPACESHOOT_WINDOW_TITLE_NAME, 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Create window failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 创建渲染器*/
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "SDL Create renderer failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 创建主场景*/
    current_scene = new MainScene();
    if (current_scene == nullptr)
    {
        std::cout << "Main Scene new failed." << std::endl;
        return;
    }
    current_scene->init();
    running_flag = true;
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
    if (current_scene != nullptr)
    {
        current_scene->clean();
        delete current_scene;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
void GameManager::update()
{
    if (current_scene != nullptr)
    {
        current_scene->update();
    }
}
void GameManager::render()
{
    /* 清空渲染器*/
    SDL_RenderClear(renderer);
    /* 绘制*/
    current_scene->render();
    /* 显示更新*/
    SDL_RenderPresent(renderer);
}
void GameManager::handle_event(SDL_Event *event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            running_flag = false;
        }
        current_scene->handle_event(event);
    }
}