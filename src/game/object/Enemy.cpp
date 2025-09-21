#include "Enemy.h"
#include "SDL_image.h"
#include "GameManager.h"
Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}
void Enemy::init()
{
    /* 配置enemy默认移动速度*/
    get_speed() = SPACESHOOT_ENEMY_DEFAULT_SPEED;
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_ENEMY_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放enemy图片*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义enemy起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
}
void Enemy::update()
{
    /* 根据enemy的位置和enemy的速度更新坐标(不需要更新x)*/
    get_point().y += get_speed() * get_game().get_speedArg();
    /* 溢出屏幕检测*/
    if (get_point().y > get_game().get_height())
    {
        /* 设置dead标志，等待被清空*/
        get_dead() = true;
    }
}
void Enemy::render()
{
    SDL_Rect Enemy_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Enemy_rect);
}
void Enemy::clean()
{
    if (get_texture() != nullptr)
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Enemy::handle_event(SDL_Event *event)
{
}