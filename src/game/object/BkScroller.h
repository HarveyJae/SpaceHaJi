#pragma once
#include "GameObject.h"
class BkScroller : public GameObject
{
public:
    enum class BkScrollerType
    {
        None = 0,
        NearStar,
        FarStar,
        BkScrollerTypeMax,
    };

private:
    BkScrollerType type = BkScrollerType::None;
    /* 背景卷轴Y偏移量*/
    float offset = 0.0f;

public:
    BkScroller(BkScrollerType type);
    ~BkScroller();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 定义访问器*/
    float &get_offset() { return offset; }
};
