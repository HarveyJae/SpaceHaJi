#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include "main.h"
int main(int, char const **)
{
    int retval = 0;
    std::cout << "Hello,SpaceShoot." << std::endl;
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
    /* SDL_ttf初始化*/
    retval = TTF_Init();
    if (retval != 0)
    {
        std::cout << "SDL_TTF Init failed: " << SDL_GetError() << std::endl;
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
    SDL_Texture *texture = IMG_LoadTexture(renderer, SPACESHOOT_BG_IMAGE_PATH);
    if (texture == nullptr)
    {
        std::cout << "Create image texture failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建字体对象*/
    TTF_Font *font = TTF_OpenFont(SPACESHOOT_BG_FONT_PATH, SPACESHOOT_TTF_SIZE_BG);
    if (font == nullptr)
    {
        std::cout << "Load font failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建文本纹理*/
    SDL_Color font_color = {255, 255, 255, 255};
    SDL_Surface *font_surface = TTF_RenderUTF8_Blended(font, "Hello, SpaceShoot.", font_color);
    if (font_surface == nullptr)
    {
        std::cout << "Create font surface failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);
    if (font_texture == nullptr)
    {
        std::cout << "Create font texture failed: " << SDL_GetError() << std::endl;
        return -1;
    }
    /* 创建音频对象*/
    Mix_Music *music = Mix_LoadMUS(SPACESHOOT_BG_MUSIC_PATH);
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

        /* 绘制文本纹理*/
        SDL_Rect text_rect = {250, 250, font_surface->w, font_surface->h};
        SDL_RenderCopy(renderer, font_texture, nullptr, &text_rect); /* 不会显示绘制结果*/

        /* 显示绘制结果*/
        SDL_RenderPresent(renderer);
    }

    /* 销毁音频对象*/
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    /* 销毁字体纹理*/
    SDL_DestroyTexture(font_texture);
    SDL_FreeSurface(font_surface);
    TTF_CloseFont(font);
    /* 销毁图片纹理*/
    SDL_DestroyTexture(texture);
    /* 销毁渲染器*/
    SDL_DestroyRenderer(renderer);
    /* 销毁窗口*/
    SDL_DestroyWindow(window);
    /* 退出SDL_mixer*/
    Mix_Quit();
    /* 退出SDL_ttf*/
    TTF_Quit();
    /* 退出SDL_image*/
    IMG_Quit();
    /* 退出SDL*/
    SDL_Quit();

    return 0;
}
