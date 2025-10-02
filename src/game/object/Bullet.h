#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <stdint.h>
#define SPACESHOOT_OBJECT_FIGHTER_BULLET_IMAGE_PATH "../assets/image/haji_bullet_fighter.png" /* fighter_bullet图片路径*/
#define SPACESHOOT_OBJECT_ENEMY_BULLET_IMAGE_PATH "../assets/image/bullet-1.png"              /* enemy_bullet图片路径*/
#define SPACESHOOT_FIGHTER_BULLET_DEFAULT_SPEED 400                                           /* fighter_bullet的速度，400px/s*/
#define SPACESHOOT_ENEMY_BULLET_DEFAULT_SPEED 200                                             /* enemy_bullet的速度，200px/s*/

/* 前向声明*/
class Enemy;
class Fighter;
class Bullet : public GameObject
{
public:
    /* 定义枚举类型*/
    enum class BulletType
    {
        None = 0,
        Fighter,
        Enemy,
        BulletTypeMax,
    };

private:
    BulletType type = BulletType::None;
    /* 射击者*/
    GameObject *master;
    /* 射击目标*/
    GameObject *target;
    /* 计算射击方向*/
    void cal_direction();

public:
    Bullet(BulletType type, GameObject *master, GameObject *target);
    ~Bullet() override;
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 定义访问器*/
    BulletType &get_type() { return type; }
};
