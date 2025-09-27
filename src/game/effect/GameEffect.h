#pragma once
#include "SDL.h"
#include <cstdint>
/* 前向声明*/
class GameManager;
class GameEffect
{
private:
    GameManager &game;
    /* 图片纹理*/
    SDL_Texture *texture = nullptr;
    /* 像素位置*/
    SDL_FPoint pos{0, 0};
    /* 尺寸(px)*/
    int width = 0;
    int height = 0;
    /* 帧率(不同特效以各自节奏播放)*/
    int FPS = 0;
    /* 帧数*/
    int total_frame = 0;
    /* 帧索引*/
    int current_frame = 0;
    /* 动画开始时间*/
    uint32_t start_time = 0;

public:
    GameEffect();
    virtual ~GameEffect() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handle_event(SDL_Event *event) = 0;

    /* 定义访问器*/
    GameManager &get_game() { return game; }
    SDL_Texture *&get_texture() { return texture; }
    SDL_FPoint &get_point() { return pos; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    int &get_fps() { return FPS; }
    int &get_totalFrame() { return total_frame; }
    int &get_curFrame() { return current_frame; }
    uint32_t get_StartTime() { return start_time; }
};
