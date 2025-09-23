#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <vector>
#include <memory>
#include <stdint.h>
#define SPACESHOOT_OBJECT_ENEMY_IMAGE_PATH "../assets/image/insect-1.png" /* enemy图片路径*/
#define SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME 2000                       /* enemy的射击冷静时间，2000ms*/
#define SPACESHOOT_ENEMY_DEFAULT_SPEED 100                                /* enemy的速度，100px/s*/

/* 前向声明*/
class Bullet;
class Enemy : public GameObject
{
private:
    /* 射击冷静时间*/
    uint32_t cooldown_time = SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME;
    /* 上次射击时间*/
    uint32_t last_shootTime = 0;

public:
    Enemy();
    ~Enemy();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 射击*/
    std::unique_ptr<Bullet> shoot_bullet(GameObject *target);
};
