#include "BkScroller.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#define SPACESHOOT_OBJECT_BKSCROLLER_NEARSTAR_IMAGE_PATH "../assets/image/Stars-A.png" /* near_star图片路径*/
#define SPACESHOOT_OBJECT_BKSCROLLER_FARSTAR_IMAGE_PATH "../assets/image/Stars-B.png"  /* far_star图片路径*/
#define SPACESHOOT_BKSCROLLER_NEARSTAR_DEFAULT_SPEED 0                                 /* near_star的速度，0px/s*/
#define SPACESHOOT_BKSCROLLER_FARSTAR_DEFAULT_SPEED 20                                 /* far_star的速度，20px/s*/
BkScroller::BkScroller(BkScrollerType type) : type(type)
{
}

BkScroller::~BkScroller()
{
}
void BkScroller::init()
{
    /* 类型越界检测*/
    if (type < BkScrollerType::None || type >= BkScrollerType::BkScrollerTypeMax)
    {
        type = BkScrollerType::None;
    }
    switch (type)
    {
    /* 避免编译警报*/
    case BkScrollerType::BkScrollerTypeMax:
    case BkScrollerType::None:
        /* nothing to do*/
        return;
    case BkScrollerType::NearStar:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BKSCROLLER_NEARSTAR_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_speed() = SPACESHOOT_BKSCROLLER_NEARSTAR_DEFAULT_SPEED;
        break;
    case BkScrollerType::FarStar:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BKSCROLLER_FARSTAR_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_speed() = SPACESHOOT_BKSCROLLER_FARSTAR_DEFAULT_SPEED;
        break;
    }
    /* 等比例缩放*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
    /* 偏移量(从下向上滚动)*/
    offset = -get_height();
}
void BkScroller::update()
{
    if (type == BkScrollerType::None)
    {
        return;
    }
    offset += get_speed() * get_game().get_speedArg();
    if (offset >= 0)
    {
        offset -= get_height();
    }
}
void BkScroller::render()
{
    for (int point_y = static_cast<int>(offset); point_y < get_game().get_height(); point_y += get_height())
    {
        for (int point_x = 0; point_x < get_game().get_width(); point_x += get_width())
        {
            SDL_Rect BkScroller_rect{point_x, point_y, get_width(), get_height()};
            SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &BkScroller_rect);
        }
    }
}
void BkScroller::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void BkScroller::handle_event(SDL_Event *event)
{
}