#include "Fighter.h"
#include "GameManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Bullet.h"
#include <memory>
Fighter::Fighter()
{
}
Fighter::~Fighter()
{
}
void Fighter::init()
{
    /* 配置fighter默认移动速度*/
    get_speed() = SPACESHOOT_FIGHTER_DEFAULT_SPEED;
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放fighter图片*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义fighter起始坐标*/
    get_point().x = get_game().get_width() / 2 - get_width() / 2;
    get_point().y = get_game().get_height() - get_height();
}
void Fighter::update()
{
    /* fighter的更新依赖于场景按键*/
}
void Fighter::render()
{
    SDL_Rect Fighter_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Fighter_rect);
}
void Fighter::clean()
{
    if (get_texture() != nullptr)
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Fighter::handle_event(SDL_Event *event)
{
}
std::unique_ptr<Bullet> Fighter::shoot_bullet()
{
    uint32_t now_shootTime = SDL_GetTicks();
    if (now_shootTime - last_shootTime >= cooldown_time)
    {
        /* 创建一个bullet智能指针*/
        auto bullet = std::make_unique<Bullet>();
        /* 初始化bullet*/
        bullet->init();
        /* 定位子弹的初始坐标(fighter上面)*/
        bullet->get_point().x = get_point().x + get_width() / 2 - bullet->get_width() / 2;
        bullet->get_point().y = get_point().y;
        /* 更新时间*/
        last_shootTime = now_shootTime;
        /* 返回bullet*/
        return bullet;
    }
    return nullptr;
}