#define SDL_MAIN_HANDLED
#include <iostream>
#include <filesystem>
#include <SDL.h>
#include "main.h"
int main(int, char const **)
{
    int retval = 0;
    std::cout << "Hello,SpaceShoot." << std::endl;
    /* 获取当前工作区路径*/
    std::filesystem::path cwd = std::filesystem::current_path();
    /* 初始化SDL*/
    retval = SDL_Init(SDL_INIT_EVERYTHING);
    if (retval != 0)
    {
        std::cout << "SDL Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* SDL_image初始化*/
    retval = IMG_Init(SPACESHOOT_IMG_FORMAT);
    if (retval != SPACESHOOT_IMG_FORMAT)
    {
        std::cout << "SDL_IMG Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* SDL_mixer初始化*/
    retval = Mix_OpenAudio(SPACESHOOT_MIX_FREQUENCY, SPACESHOOT_MIX_FORMAT, SPACESHOOT_MIX_CHANNELS, SPACESHOOT_MIX_BUFFER_SIZE);
    if (retval != 0)
    {
        std::cout << "SDL_IMG Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建SDL窗口*/
    SDL_Window *window = SDL_CreateWindow("SpaceShoot", 200, 200, 500, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Window create failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建SDL渲染器*/
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "SDL Renderer create failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建图片纹理*/
    std::filesystem::path img_bg_path = cwd / "assets" / "image" / "bg.png";
    SDL_Texture *texture = IMG_LoadTexture(renderer, img_bg_path.string().c_str());
    if (texture == nullptr)
    {
        std::cout << "Load image failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建音频对象*/
    std::filesystem::path mix_bg_path = cwd / "assets" / "music" / "03_Racing_Through_Asteroids_Loop.ogg";
    Mix_Music *music = Mix_LoadMUS(mix_bg_path.string().c_str());
    if (music == nullptr)
    {
        std::cout << "Load mix failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 播放音频*/
    Mix_PlayMusic(music, -1);

    while (SDL_TRUE)
    {
        /* 事件检测*/
        SDL_Event event;
        if (SDL_PollEvent(&event) == SDL_TRUE)
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        /* 配置渲染器为黑色*/
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        /* 清屏(本质上是使用渲染器进行全屏绘制，不会显示绘制结果)*/
        SDL_RenderClear(renderer);

        /* 创建一个长方形*/
        SDL_Rect rect = {100, 100, 200, 200};
        /* 配置渲染器为蓝色*/
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        /* 绘制长方形(使用当前渲染器配置)*/
        SDL_RenderFillRect(renderer, &rect);

        /* 绘制图片纹理*/
        SDL_Rect bg_rect = {200, 200, 100, 200};
        SDL_RenderCopy(renderer, texture, nullptr, &bg_rect); /* 不会显示绘制结果*/

        /* 显示绘制结果*/
        SDL_RenderPresent(renderer);
    }

    /* 销毁音频对象*/
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    /* 销毁图片纹理*/
    SDL_DestroyTexture(texture);
    /* 销毁渲染器*/
    SDL_DestroyRenderer(renderer);
    /* 销毁窗口*/
    SDL_DestroyWindow(window);
    /* 退出SDL_mixer*/
    Mix_Quit();
    /* 退出SDL_image*/
    IMG_Quit();
    /* 退出SDL*/
    SDL_Quit();
    
    return 0;
}
