#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <vector>
#include <memory>
#include <stdint.h>
#define SPACESHOOT_OBJECT_ENEMY_IMAGE_PATH "../assets/image/insect-1.png" /* enemy图片路径*/
#define SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME 2000                       /* enemy的射击冷静时间，2000ms*/
#define SPACESHOOT_ENEMY_DEFAULT_SPEED 100                                /* enemy的速度，100px/s*/
#define SPACESHOOT_ENEMY_DEFAULT_TOTAL_HEALTH 2                           /* enemy的总生命值*/
#define SPACESHOOT_ENEMY_DEFAULT_DAMAGE 1                                 /* enemy的伤害值*/

/* 前向声明*/
class Bullet;
class Explosion;
class Enemy : public GameObject
{
private:
    /* 射击冷静时间*/
    uint32_t cooldown_time = SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME;
    /* 上次射击时间*/
    uint32_t last_shootTime = 0;
    /* 击杀标志*/
    bool hit_flag = false;

public:
    Enemy();
    ~Enemy() override;
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 定义修改器*/
    bool &get_hitFlag() { return hit_flag; }
    /* 射击*/
    std::unique_ptr<Bullet> shoot_bullet(GameObject *target, uint32_t damage);
    /* 爆炸*/
    std::unique_ptr<Explosion> explode();
};
