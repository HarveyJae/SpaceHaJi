#include "Fighter.h"
#include "GameManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Item.h"
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
    /* 配置fighter默认生命值*/
    get_health() = SPACESHOOT_FIGHTER_DEFAULT_TOTAL_HEALTH;
    get_curHealth() = SPACESHOOT_FIGHTER_DEFAULT_TOTAL_HEALTH;
    /* 配置fighter默认伤害*/
    get_damage() = SPACESHOOT_FIGHTER_DEFAULT_DAMAGE;
    /* 加载texture*/
    get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH);
    SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放fighter图片*/
    get_width() = get_width() / 3;
    get_height() = get_height() / 3;
    /* 定义fighter起始坐标*/
    get_point().x = get_game().get_width() / 2 - get_width() / 2;
    get_point().y = get_game().get_height() - get_height();
}
void Fighter::update()
{
    /* nothing to do...*/
}
void Fighter::render()
{
    /* 绘制fighter*/
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
std::unique_ptr<Bullet> Fighter::shoot_bullet(GameObject *target, uint32_t damage)
{
    /* 无伤害 == 不发射*/
    if (damage == 0)
    {
        return nullptr;
    }
    uint32_t now_shootTime = SDL_GetTicks();
    if (now_shootTime - last_shootTime >= cooldown_time)
    {
        /* 创建一个bullet智能指针*/
        auto bullet = std::make_unique<Bullet>(Bullet::BulletType::Fighter, this, target);
        /* 初始化bullet*/
        bullet->init();
        /* 配置bullet伤害*/
        bullet->get_damage() = damage;
        /* 定位子弹的初始坐标(fighter上面)*/
        bullet->get_point().x = get_point().x + get_width() / 2 - bullet->get_width() / 2;
        bullet->get_point().y = get_point().y;
        /* 更新时间*/
        last_shootTime = now_shootTime;
        /* 添加到bullet数组中*/
        return bullet;
    }
    return nullptr;
}
std::unique_ptr<Explosion> Fighter::explode()
{
    /* 创建爆炸效果*/
    auto explosion = std::make_unique<Explosion>();
    /* 初始化*/
    explosion->init();
    /* 设置效果尺寸*/
    explosion->get_eWidth() = get_width();
    explosion->get_eHeight() = get_height();
    /* 定位爆炸坐标(宿主坐标)*/
    /* 由于宿主尺寸和效果尺寸相同，因此中心点重合*/
    explosion->get_point().x = get_point().x;
    explosion->get_point().y = get_point().y;
    return explosion;
}
void Fighter::get_item(Item *item)
{
    switch (item->get_type())
    {
    case Item::ItemType::ItemTypeMax:
    case Item::ItemType::None:
        /* nothing to do*/
        break;
    case Item::ItemType::Life:
        get_curHealth()++;
        if (get_curHealth() > get_health())
        {
            get_curHealth() = get_health();
        }
    default:
        break;
    }
}