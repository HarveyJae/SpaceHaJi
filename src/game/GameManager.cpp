#include "GameManager.h"
#include <iostream>
#include "MainScene.h"
#include "SDL.h"
#include "SDL_image.h"
GameManager::GameManager()
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
        running_flag = false;
        return;
    }
    /* 创建窗口*/
    window = SDL_CreateWindow(SPACESHOOT_WINDOW_TITLE_NAME, 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Create window failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 创建渲染器*/
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "SDL Create renderer failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 配置渲染器的默认颜色*/
    retval = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if (retval != 0)
    {
        std::cout << "SDL default color set failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 初始化SDL_image*/
    retval = IMG_Init(SPACESHOOT_IMAGE_FLAG);
    if (retval != SPACESHOOT_IMAGE_FLAG)
    {
        std::cout << "SDL_image init failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 创建主场景*/
    current_scene = new MainScene();
    if (current_scene == nullptr)
    {
        std::cout << "Main Scene new failed." << std::endl;
        running_flag = false;
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
            std::cout << "Current scene is null, quit game." << std::endl;
            return;
        }
        SDL_Event event;
        handle_event(&event); /* 处理场景事件*/
        update();             /* 更新*/
        render();             /* 绘制*/
    }
}
void GameManager::clean()
{
    if (current_scene != nullptr)
    {
        current_scene->clean();
        delete current_scene;
        /* 避免重复释放*/
        current_scene = nullptr;
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    /* 避免重复释放*/
    renderer = nullptr;
    SDL_DestroyWindow(window);
    /* 避免重复释放*/
    window = nullptr;
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
    /* 更新场景事件*/
    if (current_scene != nullptr)
    {
        current_scene->update();
    }
}
void GameManager::render()
{
    /* 清空渲染器*/
    SDL_RenderClear(renderer);
    /* 绘制场景事件*/
    if (current_scene != nullptr)
    {
        current_scene->render();
    }
    /* 显示更新*/
    SDL_RenderPresent(renderer);
}
void GameManager::handle_event(SDL_Event *event)
{
    /* 事件分发*/
    while (SDL_PollEvent(event))
    {
        /* 处理退出事件*/
        if (event->type == SDL_QUIT)
        {
            running_flag = false;
        }
        /* 处理场景事件*/
        if (current_scene != nullptr)
        {
            current_scene->handle_event(event);
        }
    }
}