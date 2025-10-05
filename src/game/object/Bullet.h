#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <stdint.h>
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
        HAJI_1,
        MANBO,
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
