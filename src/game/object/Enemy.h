#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <vector>
#include <memory>
#include <stdint.h>
#define SPACESHOOT_OBJECT_ENEMY_HAJI_1_IMAGE_PATH "../assets/image/haji_enemy3.png" /* enemy_haji_2图片路径*/
#define SPACESHOOT_OBJECT_ENEMY_MANBO_IMAGE_PATH "../assets/image/haji_enemy2.png"  /* enemy_manbo图片路径*/
#define SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME 3000                                 /* enemy的射击冷静时间，3000ms*/
#define SPACESHOOT_ENEMY_DEFAULT_SPEED 100                                          /* enemy的速度，100px/s*/
#define SPACESHOOT_ENEMY_HAJI_1_DEFAULT_TOTAL_HEALTH 2                              /* enemy_haji_1的总生命值*/
#define SPACESHOOT_ENEMY_HAJI_1_DEFAULT_DAMAGE 1                                    /* enemy_haji_1的伤害值*/
#define SPACESHOOT_ENEMY_HAJI_2_DEFAULT_TOTAL_HEALTH 4                              /* enemy_haji_2的总生命值*/
#define SPACESHOOT_ENEMY_HAJI_2_DEFAULT_DAMAGE 2                                    /* enemy_haji_2的伤害值*/
#define SPACESHOOT_ENEMY_MANBO_DEFAULT_TOTAL_HEALTH 3                               /* enemy_manbo的总生命值*/
#define SPACESHOOT_ENEMY_MANBO_DEFAULT_DAMAGE 1                                     /* enemy_manbo的伤害值*/
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
    uint32_t cooldown_time = SPACESHOOT_ENEMY_DEFAULT_COLLDOWN_TIME;
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
