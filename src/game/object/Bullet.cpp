#include "Bullet.h"
#include "SDL_image.h"
#include "GameManager.h"
#include <cmath>
#include <cstdint>
#define SPACESHOOT_OBJECT_FIGHTER_BULLET_IMAGE_PATH "../assets/image/haji_bullet_fighter.png" /* fighter_bullet图片路径*/
#define SPACESHOOT_OBJECT_HAJI1_BULLET_IMAGE_PATH "../assets/image/bullet-2.png"              /* haji1_bullet图片路径*/
#define SPACESHOOT_OBJECT_MANBO_BULLET_IMAGE_PATH "../assets/image/bullet-1.png"              /* manbo_bullet图片路径*/
#define SPACESHOOT_FIGHTER_BULLET_DEFAULT_SPEED 400                                           /* fighter_bullet的速度，400px/s*/
#define SPACESHOOT_HAJI1_BULLET_DEFAULT_SPEED 200                                             /* haji1_bullet的速度，200px/s*/
#define SPACESHOOT_MANBO_BULLET_DEFAULT_SPEED 150                                             /* manbo_bullet的速度，100px/s*/
Bullet::Bullet(BulletType type, GameObject *master, GameObject *target) : type(type), master(master), target(target)
{
}
Bullet::~Bullet()
{
}
void Bullet::init()
{
    /* 类型越界检测*/
    if (type < BulletType::None || type >= BulletType::BulletTypeMax)
    {
        type = BulletType::None;
    }
    switch (type)
    {
    /* 避免编译警报*/
    case BulletType::BulletTypeMax:
    case BulletType::None:
        /* nothing to do*/
        return;
    case BulletType::Fighter:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_FIGHTER_BULLET_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_speed() = SPACESHOOT_FIGHTER_BULLET_DEFAULT_SPEED;
        get_width() = get_width() / 20;
        get_height() = get_height() / 20;
        break;
    case BulletType::HAJI_1:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_HAJI1_BULLET_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_speed() = SPACESHOOT_HAJI1_BULLET_DEFAULT_SPEED;
        get_width() = get_width() / 2;
        get_height() = get_height() / 2;
        break;
    case BulletType::MANBO:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_MANBO_BULLET_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_speed() = SPACESHOOT_MANBO_BULLET_DEFAULT_SPEED;
        get_width() = get_width() / 2;
        get_height() = get_height() / 2;
        break;
    }
    /* 计算射击方向*/
    cal_direction();
    /* 定义bullet起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
}
void Bullet::update()
{
    switch (type)
    {
    /* 避免编译警报*/
    case BulletType::BulletTypeMax:
    case BulletType::None:
        /* nothing to do*/
        break;
    case BulletType::Fighter:
        /* 根据速度更新坐标(不需要更新x)*/
        get_point().y += get_direction().y * get_speed() * get_game().get_speedArg();
        /* 边界判断*/
        if (get_point().y < 0)
        {
            /* 设置dead标志，等待被清空*/
            get_dead() = true;
        }
        break;
    case BulletType::HAJI_1:
    case BulletType::MANBO:
        /* 根据速度更新坐标*/
        get_point().y += get_direction().y * get_speed() * get_game().get_speedArg();
        get_point().x += get_direction().x * get_speed() * get_game().get_speedArg();
        /* 边界判断*/
        if (get_point().y < 0 || get_point().y > get_game().get_height() || get_point().x < 0 || get_point().x > get_game().get_width())
        {
            /* 设置dead标志，等待被清空*/
            get_dead() = true;
        }
        break;
    }
}
void Bullet::render()
{
    /* 定义绘制dest区域*/
    SDL_Rect Bullet_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    switch (type)
    {
    /* 避免编译警报*/
    case BulletType::BulletTypeMax:
    case BulletType::None:
        /* nothing to do*/
        break;
    case BulletType::Fighter:
        /* 非旋转绘制*/
        SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Bullet_rect);
        break;
    case BulletType::HAJI_1:
    case BulletType::MANBO:
        /* 计算方向角度(x轴为基准)*/
        float angle = std::atan2(get_direction().y, get_direction().x) * 180.0 / M_PI - 90;
        /* 旋转中心*/
        SDL_Point center{get_width() / 2, get_height() / 2};
        /* 旋转绘制*/
        SDL_RenderCopyEx(get_game().get_renderer(), get_texture(), nullptr, &Bullet_rect, angle, &center, SDL_FLIP_NONE);
        break;
    }
}
void Bullet::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Bullet::handle_event(SDL_Event *event)
{
}
void Bullet::cal_direction()
{
    switch (type)
    {
    /* 避免编译警报*/
    case BulletType::BulletTypeMax:
    case BulletType::None:
        /* nothing to do*/
        break;
    case BulletType::Fighter:
        /* 固定方向*/
        get_direction().x = 0.0f;
        get_direction().y = -1.0f;
        break;
    case BulletType::HAJI_1:
    case BulletType::MANBO:
        if (!master || !target)
        {
            /* 固定方向*/
            get_direction().x = 0.0f;
            get_direction().y = 1.0f;
            break;
        }
        /* 计算从master中心到target中心的向量*/
        auto x = (target->get_point().x + target->get_width() / 2) - (master->get_point().x + master->get_width() / 2);
        auto y = (target->get_point().y + target->get_height() / 2) - (master->get_point().y + master->get_height() / 2);
        /* 计算向量长度*/
        auto length = std::sqrt(x * x + y * y);
        if (length == 0.0f)
        {
            /* master与target重叠时保持默认方向*/
            get_direction().x = 0.0f;
            get_direction().y = 1.0f;
        }
        else
        {
            /* 向量归一化*/
            get_direction().x = x / length;
            get_direction().y = y / length;
        }
        break;
    }
}
