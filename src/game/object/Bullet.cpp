#include "Bullet.h"
#include "SDL_image.h"
#include "GameManager.h"
Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}
void Bullet::init()
{
    /* 配置bullet默认移动速度*/
    get_speed() = SPACESHOOT_BULLET_DEFAULT_SPEED;
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_BULLET_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放bullet图片*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义bullet起始坐标*/
    get_point().x = get_game().get_width() / 2 - get_width() / 2;
    get_point().y = get_game().get_height() - get_height();
}
void Bullet::update()
{
    /* 根据bullet的位置和bullet的速度更新(不需要更新x)*/
    get_point().y -= get_speed() * get_game().get_speedArg();
    if (get_point().y < 0)
    {
        /* 设置dead标志，等待被清空*/
        get_dead() = true;
    }
}
void Bullet::render()
{
    SDL_Rect Bullet_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Bullet_rect);
}
void Bullet::clean()
{
    if (get_texture() != nullptr)
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Bullet::handle_event(SDL_Event *event)
{
}