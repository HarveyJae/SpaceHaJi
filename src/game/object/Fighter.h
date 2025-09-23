#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <stdint.h>
#define SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH "../assets/image/SpaceShip.png" /* fighter图片路径*/
#define SPACESHOOT_FIGHTER_DEFAULT_SPEED 200                                 /* fighter的速度，200px/s*/
#define SPACESHOOT_FIGHTER_DEFAULT_COLLDOWN_TIME 500                         /* fighter的射击冷静时间，500ms*/

/* 前置声明*/
class Bullet;
class Fighter : public GameObject
{
private:
    /* 射击冷静时间*/
    uint32_t cooldown_time = SPACESHOOT_FIGHTER_DEFAULT_COLLDOWN_TIME;
    /* 上次射击时间*/
    uint32_t last_shootTime = 0;

public:
    Fighter();
    ~Fighter();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 射击*/
    std::unique_ptr<Bullet> shoot_bullet(GameObject *target);
};
