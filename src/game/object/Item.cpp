#include "Item.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#define SPACESHOOT_OBJECT_BONUS_LIFE_IMAGE_PATH "../assets/image/bonus_life.png"    /* bonus_life的图片路径*/
#define SPACESHOOT_OBJECT_BONUS_SHIED_IMAGE_PATH "../assets/image/bonus_shield.png" /* bonus_shield的图片路径*/
#define SPACESHOOT_OBJECT_BONUS_TIME_IMAGE_PATH "../assets/image/bonus_time.png"    /* bonus_time的图片路径*/
#define SPACESHOOT_BONUS_LIFE_DEFAULT_SPEED 200                                     /* bonus_life的速度，200px/s*/
#define SPACESHOOT_BONUS_SHIED_DEFAULT_SPEED 200                                    /* bonus_shield的速度，200px/s*/
#define SPACESHOOT_BONUS_TIME_DEFAULT_SPEED 200                                     /* bonus_time的速度，200px/s*/
#define SPACESHOOT_BONUS_LIFE_DEFAULT_BOUND_CNT 3                                   /* bonus_life的碰撞次数，3*/
#define SPACESHOOT_BONUS_SHIED_DEFAULT_BOUND_CNT 2                                  /* bonus_life的碰撞次数，2*/
#define SPACESHOOT_BONUS_TIME_DEFAULT_BOUND_CNT 2                                   /* bonus_life的碰撞次数，2*/
Item::Item(ItemType type) : type(type)
{
}
Item::~Item()
{
}
void Item::init()
{
    /* 类型越界检测*/
    if (type < ItemType::None || type >= ItemType::ItemTypeMax)
    {
        type = ItemType::None;
    }
    switch (type)
    {
    /* 避免编译警报*/
    case ItemType::ItemTypeMax:
    case ItemType::None:
        /* nothing to do*/
        return;
    case ItemType::Life:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BONUS_LIFE_IMAGE_PATH);
        get_speed() = SPACESHOOT_BONUS_LIFE_DEFAULT_SPEED;
        get_boundCnt() = SPACESHOOT_BONUS_LIFE_DEFAULT_BOUND_CNT;
        break;
    case ItemType::Shield:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BONUS_SHIED_IMAGE_PATH);
        get_speed() = SPACESHOOT_BONUS_SHIED_DEFAULT_SPEED;
        get_boundCnt() = SPACESHOOT_BONUS_SHIED_DEFAULT_BOUND_CNT;
        break;
    case ItemType::Time:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BONUS_TIME_IMAGE_PATH);
        get_speed() = SPACESHOOT_BONUS_TIME_DEFAULT_SPEED;
        get_boundCnt() = SPACESHOOT_BONUS_TIME_DEFAULT_BOUND_CNT;
        break;
    default:
        break;
    }
    SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放item图片*/
    get_width() = get_width() / 4;
    get_height() = get_height() / 4;
    /* 计算随机方向*/
    cal_direction();
    /* 定义item起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
}
void Item::update()
{
    /* 根据速度更新坐标*/
    get_point().y += get_direction().y * get_speed() * get_game().get_speedArg();
    get_point().x += get_direction().x * get_speed() * get_game().get_speedArg();
    /* 边界判断*/
    if (get_point().y < 0 && bound_count > 0)
    {
        /* 屏幕上边缘*/
        get_direction().y = -get_direction().y;
        bound_count--;
    }
    else if (get_point().y > get_game().get_height() && bound_count > 0)
    {
        /* 屏幕下边缘*/
        get_direction().y = -get_direction().y;
        bound_count--;
    }
    else if (get_point().x < 0 && bound_count > 0)
    {
        /* 屏幕左边缘*/
        get_direction().x = -get_direction().x;
        bound_count--;
    }
    else if (get_point().x > get_game().get_width() && bound_count > 0)
    {
        get_direction().x = -get_direction().x;
        bound_count--;
    }

    /* 碰撞次数判断*/
    if (bound_count < 0)
    { 
        /* 设置dead标志，等待被清空*/
        get_dead() = true;
    }
}
void Item::render()
{
    SDL_Rect Item_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Item_rect);
}
void Item::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Item::handle_event(SDL_Event *event)
{
}
void Item::cal_direction()
{
    /* 使用cos和sin省略向量归一化的过程*/
    float angle = get_game().random() * 2 * M_PI;
    get_direction().x = std::cos(angle);
    get_direction().y = std::sin(angle);
}