#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>
#include <stdint.h>
/* 前置声明*/
class Bullet;
class Explosion;
class Item;
class Fighter : public GameObject
{
private:
    /* 射击冷静时间*/
    uint32_t cooldown_time = 0;
    /* 上次射击时间*/
    uint32_t last_shootTime = 0;
    /* 击杀分数*/
    int score = 0;

public:
    Fighter();
    ~Fighter() override;
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 定义修改器*/
    int &get_score() { return score; }
    /* 射击*/
    std::unique_ptr<Bullet> shoot_bullet(GameObject *target, uint32_t damage);
    std::unique_ptr<Bullet> shoot_rocket(GameObject *target, uint32_t damage);
    /* 爆炸*/
    std::unique_ptr<Explosion> explode();
    /* 拾取物品*/
    void get_item(Item *item);
};
