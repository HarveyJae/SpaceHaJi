#include "Shield.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#define SPACESHOOT_OBJECT_SHIELD_IMAGE_PATH "../assets/image/shield.png" /* shield的图片路径*/
#define SPACESHOOT_SHIELD_TIMER (15 * 1000)                              /* shield持续时间，15s*/
#define SPACESHOOT_SHIELD_DEFAULT_TOTAL_HEALTH 20                        /* shield的总生命值*/
Shield::Shield()
{
}

Shield::~Shield()
{
}
void Shield::init()
{
    /* 设置shield生命值*/
    get_health() = SPACESHOOT_SHIELD_DEFAULT_TOTAL_HEALTH;
    get_curHealth() = SPACESHOOT_SHIELD_DEFAULT_TOTAL_HEALTH;
    /* 加载texture*/
    get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_SHIELD_IMAGE_PATH);
    SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放尺寸*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 4;
    /* 定义shield起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
    /* 初始化启动时间*/
    timer = 0;
    /* 初始化标志*/
    get_dead() = false;
    get_active() = true;
}
void Shield::update()
{
    /* 定时器计时*/
    timer += get_game().get_frameTime();
    if (timer >= SPACESHOOT_SHIELD_TIMER)
    {
        /* 定时器计时结束*/
        get_dead() = true;
        timer = 0;
    }
}
void Shield::render()
{
    SDL_Rect Shield_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Shield_rect);
}
void Shield::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Shield::handle_event(SDL_Event *event)
{
}