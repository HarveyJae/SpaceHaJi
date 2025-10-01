#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include <cstdint>
/* 前向声明*/
class GameManager;
class GameEffect
{
private:
    GameManager &game;
    /* 图片纹理*/
    SDL_Texture *texture = nullptr;
    /* 音频对象*/
    Mix_Music *music = nullptr;
    /* 像素位置*/
    SDL_FPoint pos{0, 0};
    /* 精灵图帧尺寸(px)*/
    int width = 0;
    int height = 0;
    /* 效果尺寸*/
    int e_width = 0;
    int e_height = 0;
    /* 帧率(不同特效以各自节奏播放)*/
    int FPS = 0;
    /* 帧时间(ms/帧)*/
    uint32_t frame_time = 0;
    /* 速度参数*/
    float speed_arg = 0;
    /* 帧数*/
    int total_frame = 0;
    /* 帧索引*/
    int current_frame = 0;
    /* 完成标志*/
    bool finish_flag = false;
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
    Mix_Music *&get_music() { return music; }
    SDL_FPoint &get_point() { return pos; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    int &get_eWidth() { return e_width; }
    int &get_eHeight() { return e_height; }
    int &get_fps() { return FPS; }
    uint32_t &get_frameTime() { return frame_time; }
    float &get_speedArg() { return speed_arg; }
    int &get_totalFrame() { return total_frame; }
    int &get_curFrame() { return current_frame; }
    bool &get_finish() { return finish_flag; }
    uint32_t &get_startTime() { return start_time; }
};
