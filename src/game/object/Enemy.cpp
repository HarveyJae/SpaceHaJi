#include "Enemy.h"
#include "SDL_image.h"
#include "Bullet.h"
#include "Explosion.h"
#include "GameManager.h"
#include "Item.h"
#include <memory>
Enemy::Enemy(EnemyType type) : type(type)
{
}
Enemy::~Enemy()
{
}
void Enemy::init()
{
    /* 类型越界检测*/
    if (type < EnemyType::None || type >= EnemyType::EnemyTypeMax)
    {
        type = EnemyType::None;
    }
    switch (type)
    {
    /* 避免编译警告*/
    case EnemyType::EnemyTypeMax:
    case EnemyType::None:
        /* nothing to do*/
        return;
    case EnemyType::HAJI_1:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_ENEMY_HAJI_1_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_width() = get_width() / 2;
        get_height() = get_height() / 2;
        get_health() = SPACESHOOT_ENEMY_HAJI_2_DEFAULT_TOTAL_HEALTH;
        get_curHealth() = SPACESHOOT_ENEMY_HAJI_2_DEFAULT_TOTAL_HEALTH;
        get_damage() = SPACESHOOT_ENEMY_HAJI_2_DEFAULT_DAMAGE;
        break;
    case EnemyType::MANBO:
        get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_ENEMY_MANBO_IMAGE_PATH);
        SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
        get_width() = get_width() / 2;
        get_height() = get_height() / 2;
        get_health() = SPACESHOOT_ENEMY_MANBO_DEFAULT_TOTAL_HEALTH;
        get_curHealth() = SPACESHOOT_ENEMY_MANBO_DEFAULT_TOTAL_HEALTH;
        get_damage() = SPACESHOOT_ENEMY_MANBO_DEFAULT_DAMAGE;
        break;
    }
    /* 配置enemy默认移动速度*/
    get_speed() = SPACESHOOT_ENEMY_DEFAULT_SPEED;
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
std::unique_ptr<Bullet> Enemy::shoot_bullet(GameObject *target, uint32_t damage)
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
        auto bullet = std::make_unique<Bullet>(Bullet::BulletType::Enemy, this, target);
        /* 初始化bullet*/
        bullet->init();
        /* 配置bullet伤害*/
        bullet->get_damage() = damage;
        /* 定位子弹的初始坐标(enemy中央发射)*/
        bullet->get_point().x = get_point().x + get_width() / 2 - bullet->get_width() / 2;
        bullet->get_point().y = get_point().y + get_height() / 2 - bullet->get_height() / 2;
        /* 更新时间*/
        last_shootTime = now_shootTime;
        return bullet;
    }
    return nullptr;
}
std::unique_ptr<Explosion> Enemy::explode()
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
std::unique_ptr<Item> Enemy::drop_item()
{
    /* 等概率掉落*/
    const float item_random = get_game().random();
    Item::ItemType type = Item::ItemType::None;
    const int max_index = static_cast<int>(Item::ItemType::ItemTypeMax);
    if (item_random < 1.0 / (float)(max_index - 1))
    {
        type = Item::ItemType::Life;
    }
    else if (item_random < 2.0 / (float)(max_index - 1))
    {
        type = Item::ItemType::Shield;
    }
    else
    {
        type = Item::ItemType::Time;
    }
    auto item = std::make_unique<Item>(type);
    /* 初始化item*/
    item->init();
    /* 设置item初始坐标(中心点)*/
    item->get_point().x = get_point().x + get_width() / 2 - item->get_width() / 2;
    item->get_point().y = get_point().y + get_height() / 2 - item->get_height() / 2;

    return item;
}