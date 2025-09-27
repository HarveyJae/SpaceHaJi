#pragma once
#include <SDL.h>
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
};
