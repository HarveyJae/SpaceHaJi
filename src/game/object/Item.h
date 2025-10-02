#pragma once
#include "GameObject.h"
#include "SDL.h"
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
