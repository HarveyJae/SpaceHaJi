#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <stdint.h>
#define SPACESHOOT_OBJECT_FIGHTER_BULLET_IMAGE_PATH "../assets/image/bullet.png" /* fighter_bullet图片路径*/
#define SPACESHOOT_OBJECT_ENEMY_BULLET_IMAGE_PATH "../assets/image/bullet-1.png" /* enemy_bullet图片路径*/
#define SPACESHOOT_FIGHTER_BULLET_DEFAULT_SPEED 400                              /* fighter_bullet的速度，400px/s*/
#define SPACESHOOT_ENEMY_BULLET_DEFAULT_SPEED 200                                /* enemy_bullet的速度，200px/s*/

/* 前向声明*/
class Enemy;
class Fighter;
class Bullet : public GameObject
{
private:
    uint8_t type = NONE_BULLET;
    /* bullet的方向*/
    SDL_FPoint direction = {0, 0};

public:
    Bullet(uint8_t type);
    ~Bullet();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 计算射击方向*/
    void cal_direction(GameObject *master, GameObject *target);

    /* 定义修改器*/
    SDL_FPoint &get_direction() { return direction; }
    /* 定义Bullet类型*/
    enum type
    {
        NONE_BULLET = 0, /* 初始值*/
        FIGHTER_BULLET,
        ENEMY_BULLET,
    };
};
