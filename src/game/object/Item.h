#pragma once
#include "GameObject.h"
#include "SDL.h"
#define SPACESHOOT_OBJECT_BONUS_LIFE_IMAGE_PATH "../assets/image/bonus_life.png"    /* bonus_life的图片路径*/
#define SPACESHOOT_OBJECT_BONUS_SHIED_IMAGE_PATH "../assets/image/bonus_shield.png" /* bonus_shield的图片路径*/
#define SPACESHOOT_OBJECT_BONUS_TIME_IMAGE_PATH "../assets/image/bonus_time.png"    /* bonus_time的图片路径*/
#define SPACESHOOT_BONUS_LIFE_DEFAULT_SPEED 200                                     /* bonus_life的速度，200px/s*/
#define SPACESHOOT_BONUS_SHIED_DEFAULT_SPEED 200                                    /* bonus_shield的速度，200px/s*/
#define SPACESHOOT_BONUS_TIME_DEFAULT_SPEED 200                                     /* bonus_time的速度，200px/s*/
#define SPACESHOOT_BONUS_LIFE_DEFAULT_BOUND_CNT 3                                   /* bonus_life的碰撞次数，3*/
#define SPACESHOOT_BONUS_SHIED_DEFAULT_BOUND_CNT 2                                  /* bonus_life的碰撞次数，2*/
#define SPACESHOOT_BONUS_TIME_DEFAULT_BOUND_CNT 2                                   /* bonus_life的碰撞次数，2*/
class Item : public GameObject
{
public:
    /* 物品类型枚举定义*/
    enum class ItemType
    {
        None = 0,
        Life,
        Shield,
        Time,
        ItemTypeMax,
    };

private:
    /* 允许碰撞次数*/
    int bound_count = 0;
    /* 物品类型*/
    ItemType type = ItemType::None;
    /* 计算方向*/
    void cal_direction();

public:
    Item(ItemType type);
    ~Item() override;
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 定义访问器*/
    int &get_boundCnt() { return bound_count; }
    ItemType &get_type() { return type; }
};
