#include "Bullet.h"
#include "SDL_image.h"
#include "GameManager.h"
#include <cmath>
#include <cstdint>
Bullet::Bullet(uint8_t type)
{
    this->type = type;
}
Bullet::~Bullet()
{
}
void Bullet::init()
{
    SDL_Texture *texture = nullptr;
    if (type == FIGHTER_BULLET)
    {
        /* 配置速度*/
        get_speed() = SPACESHOOT_FIGHTER_BULLET_DEFAULT_SPEED;
        /* 加载图片*/
        texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_FIGHTER_BULLET_IMAGE_PATH);
    }
    else if (type == ENEMY_BULLET)
    {
        /* 配置速度*/
        get_speed() = SPACESHOOT_ENEMY_BULLET_DEFAULT_SPEED;
        /* 加载图片*/
        texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_ENEMY_BULLET_IMAGE_PATH);
    }
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义bullet起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
}
void Bullet::update()
{
    if (type == FIGHTER_BULLET)
    {
        /* 根据速度更新坐标(不需要更新x)*/
        get_point().y += direction.y * get_speed() * get_game().get_speedArg();
        /* 边界判断*/
        if (get_point().y < 0)
        {
            /* 设置dead标志，等待被清空*/
            get_dead() = true;
        }
    }
    else if (type == ENEMY_BULLET)
    {
        /* 根据速度更新坐标*/
        get_point().y += direction.y * get_speed() * get_game().get_speedArg();
        get_point().x += direction.x * get_speed() * get_game().get_speedArg();
        /* 边界判断*/
        if (get_point().y < 0 || get_point().y > get_game().get_height() || get_point().x < 0 || get_point().x > get_game().get_width())
        {
            /* 设置dead标志，等待被清空*/
            get_dead() = true;
        }
    }
}
void Bullet::render()
{
    SDL_Rect Bullet_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    /* 旋转enemy的bullet，时刻朝向fighter*/
    if (type == ENEMY_BULLET)
    {
        /* 计算方向角度(x轴为基准)*/
        float angle = std::atan2(direction.y, direction.x) * 180.0 / M_PI - 90;
        /* 旋转中心*/
        SDL_Point center{get_width() / 2, get_height() / 2};
        /* 旋转绘制*/
        SDL_RenderCopyEx(get_game().get_renderer(), get_texture(), nullptr, &Bullet_rect, angle, &center, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Bullet_rect);
    }
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
/**
 * @brief: bullet初始化前调用
 */
void Bullet::cal_direction(GameObject *master, GameObject *target)
{
    if (master == nullptr || target == nullptr)
    {
        if (type == Bullet::FIGHTER_BULLET)
        {
            direction.x = 0.0f;
            direction.y = -1.0f;
        }
        else if (type == Bullet::ENEMY_BULLET)
        {
            direction.x = 0.0f;
            direction.y = 1.0f;
        }
        return;
    }
    /* 计算从master中心到target中心的向量*/
    auto x = (target->get_point().x + target->get_width() / 2) - (master->get_point().x + master->get_width() / 2);
    auto y = (target->get_point().y + target->get_height() / 2) - (master->get_point().y + master->get_height() / 2);

    /* 计算向量长度*/
    auto length = std::sqrt(x * x + y * y);

    if (length == 0.0f)
    {
        /* master 与 target 重叠时保持默认方向*/
        direction.x = 0.0f;
        direction.y = (type == Bullet::FIGHTER_BULLET) ? -1.0f : 1.0f;
        return;
    }

    /* 射击方向(向量归一化)*/
    direction.x = x / length;
    direction.y = y / length;
}
