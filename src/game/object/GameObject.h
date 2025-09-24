#pragma once
#include <SDL.h>
#include <stdint.h>
/* 前向声明*/
class GameManager;
/**
 * @brief: 定义物体类
 */
class GameObject
{
private:
    GameManager &game;
    /* 图片纹理*/
    SDL_Texture *texture = nullptr;
    /* 像素位置*/
    SDL_FPoint pos{0, 0};
    /* 颜色(默认为纯白)*/
    SDL_Color color{255, 255, 255, 255};
    /* 尺寸(px)*/
    int width = 0;
    int height = 0;
    /* 移动速度(px/s)*/
    int speed = 0;
    /* 总生命值*/
    uint32_t health = 0;
    /* 当前生命值*/
    uint32_t current_health = 0;
    /* 伤害值*/
    uint32_t damage = 0;
    /* 生命标志位*/
    bool active = false; /* 活动标志*/
    bool dead = false;   /* 删除标志*/
public:
    GameObject();
    virtual ~GameObject() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
    virtual void handle_event(SDL_Event *event) = 0;
    /* 定义访问器/修改器*/
    GameManager &get_game() { return game; }
    SDL_Texture *&get_texture() { return texture; }
    SDL_FPoint &get_point() { return pos; }
    SDL_Color &get_color() { return color; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    int &get_speed() { return speed; }
    uint32_t &get_health() { return health; }
    uint32_t &get_curHealth() { return current_health; }
    uint32_t &get_damage() { return damage; }
    bool &get_active() { return active; }
    bool &get_dead() { return dead; }
};
