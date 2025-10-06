#include "Thruster.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#define SPACESHOOT_OBJECT_THRUSTER_IMAGE_PATH "../assets/image/support.png" /* thruster的图片路径*/
#define SPACESHOOT_THRUSTER_TIMER (15 * 1000)                               /* thruster持续时间，15s*/
#define SPACESHOOT_THRUSTER_DEFAULT_TOTAL_HEALTH 20                         /* thruster的总生命值*/
Thruster::Thruster()
{
}

Thruster::~Thruster()
{
}
void Thruster::init()
{ /* 设置shield生命值*/
    get_health() = SPACESHOOT_THRUSTER_DEFAULT_TOTAL_HEALTH;
    get_curHealth() = SPACESHOOT_THRUSTER_DEFAULT_TOTAL_HEALTH;
    /* 加载texture*/
    get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_THRUSTER_IMAGE_PATH);
    SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放尺寸*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义shield起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
    /* 初始化启动时间*/
    timer = 0;
    /* 初始化标志*/
    get_dead() = false;
    get_active() = true;
}
void Thruster::update()
{
    if (get_active())
    {
        /* 定时器计时*/
        timer += get_game().get_frameTime();
        if (timer >= SPACESHOOT_THRUSTER_TIMER)
        {
            /* 定时器计时结束*/
            get_dead() = true;
            timer = 0;
        }
    }
}
void Thruster::render()
{
    SDL_Rect Shield_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Shield_rect);
}
void Thruster::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Thruster::handle_event(SDL_Event *event)
{
}