#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <vector>
#include <memory>
#include <stdint.h>

/* 前向声明*/
class Bullet;
class Explosion;
class Item;
class Enemy : public GameObject
{
public:
    /* enemy枚举类型定义*/
    enum class EnemyType
    {
        None = 0,
        HAJI_1,
        MANBO,
        EnemyTypeMax,
    };

private:
    /* 射击冷静时间*/
    uint32_t cooldown_time = 0;
    /* 上次射击时间*/
    uint32_t last_shootTime = 0;
    /* enemy类型*/
    EnemyType type = EnemyType::None;

public:
    Enemy(EnemyType type);
    ~Enemy() override;
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 射击*/
    std::unique_ptr<Bullet> shoot_bullet(GameObject *target, uint32_t damage);
    /* 爆炸*/
    std::unique_ptr<Explosion> explode();
    /* 掉落物品*/
    std::unique_ptr<Item> drop_item();
};
