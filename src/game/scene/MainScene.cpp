#include "MainScene.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#include "Enemy.h"
#include "BkScroller.h"
#include "Fighter.h"
#include "Bullet.h"
#include "Item.h"
#include "Explosion.h"
#include "HudManager.h"
#include "HudState.h"
#include <iostream>
#include <memory>
#include <vector>
#include <random>
#define SPACESHOOT_MAINSCENE_MUSIC_PATH "../assets/music/manbobo.mp3"          /* mainscene的背景音乐路径*/
#define SPACESHOOT_FIGHTER_SHOOT_SOUND_PATH "../assets/sound/laser_shoot4.wav" /* fighter-shoot的音效路径*/
#define SPACESHOOT_ENEMY_SHOOT_SOUND_PATH "../assets/sound/xs_laser.wav"       /* enemy-shoot的音效路径*/
#define SPACESHOOT_FIGHTER_EXPLODE_SOUND_PATH "../assets/sound/explosion1.wav" /* fighter-explode的音效路径*/
#define SPACESHOOT_ENEMY_EXPLODE_SOUND_PATH "../assets/sound/ohyeah.mp3"       /* enemy-explode的音效路径*/
#define SPACESHOOT_HIT_SOUND_PATH "../assets/sound/eff11.wav"                  /* bullet-hit的音效路径*/
#define SPACESHOOT_FIGHTER_BONUS_SOUND_PATH "../assets/sound/eff5.mp3"         /* fighter-bonus的音效路径*/
#define SPACESHOOT_FIGHTER_SHOOT_SOUND_KEY "fighter_shoot"                     /* fighter-shoot的key值*/
#define SPACESHOOT_ENEMY_SHOOT_SOUND_KEY "enemy_shoot"                         /* enemy-shoot的key值*/
#define SPACESHOOT_FIGHTER_EXPLODE_SOUND_KEY "fighter_explode"                 /* fighter-explode的key值*/
#define SPACESHOOT_ENEMY_EXPLODE_SOUND_KEY "enemy_explode"                     /* enemy-explode的key值*/
#define SPACESHOOT_HIT_SOUND_SOUND_KEY "bullet_hit"                            /* bullet-hit的key值*/
#define SPACESHOOT_FIGHTER_BONUS_SOUND_KEY "fighter_bonus"                     /* fighter-bonus的key值*/
MainScene::MainScene() : fighter(std::make_unique<Fighter>()),
                         nearStar(std::make_unique<BkScroller>(BkScroller::BkScrollerType::NearStar)),
                         farStar(std::make_unique<BkScroller>(BkScroller::BkScrollerType::FarStar))
{
}

MainScene::~MainScene()
{
}
void MainScene::init()
{
    /* 设置hud场景类型*/
    get_game().get_hud().set_sceneType(HudManager::HudSceneType::Main);
    /* 加载背景音乐*/
    get_music() = Mix_LoadMUS(SPACESHOOT_MAINSCENE_MUSIC_PATH);
    if (!get_music())
    {
        std::cout << "MainScene music load failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 开启背景音乐*/
    Mix_PlayMusic(get_music(), -1);
    /* 读取音效资源*/
    get_sounds().insert(std::make_pair(SPACESHOOT_FIGHTER_SHOOT_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_FIGHTER_SHOOT_SOUND_PATH)));
    get_sounds().insert(std::make_pair(SPACESHOOT_ENEMY_SHOOT_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_ENEMY_SHOOT_SOUND_PATH)));
    get_sounds().insert(std::make_pair(SPACESHOOT_FIGHTER_EXPLODE_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_FIGHTER_EXPLODE_SOUND_PATH)));
    get_sounds().insert(std::make_pair(SPACESHOOT_ENEMY_EXPLODE_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_ENEMY_EXPLODE_SOUND_PATH)));
    get_sounds().insert(std::make_pair(SPACESHOOT_HIT_SOUND_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_HIT_SOUND_PATH)));
    get_sounds().insert(std::make_pair(SPACESHOOT_FIGHTER_BONUS_SOUND_KEY, Mix_LoadWAV(SPACESHOOT_FIGHTER_BONUS_SOUND_PATH)));
    /* 初始化Fighter对象*/
    if (fighter)
    {
        fighter->init();
    }
    /* 初始化BkScroller对象*/
    if (nearStar)
    {
        nearStar->init();
    }
    if (farStar)
    {
        farStar->init();
    }
}
void MainScene::update()
{
    /* 场景键盘操作*/
    keyboard_ctrl();
    /* 更新fighter*/
    update_fighter();
    /* 更新bkScroller*/
    update_bkScroller();
    /* 按既定概率创建enemy*/
    create_enemy();
    /* 更新enemy*/
    update_enemy();
    /* 更新bullet*/
    update_bullet();
    /* 更新item*/
    update_item();
    /* 更新explosion*/
    update_explosion();
    /* 更新hud_manager*/
    update_hudManager();
}
void MainScene::render()
{
    /* 绘制fighter帧*/
    render_fighter();
    /* 绘制bkScroller*/
    render_bkScroller();
    /* 绘制enemy*/
    render_enemy();
    /* 绘制bullet*/
    render_bullet();
    /* 绘制item*/
    render_item();
    /* 绘制explosion*/
    render_explosion();
    /* 绘制hud_manager*/
    render_hudManager();
}
void MainScene::clean()
{
    /* 清除fighter*/
    clean_fighter();
    /* 清除bkscroller*/
    clean_bkScroller();
    /* 清除enemy*/
    clean_enemy();
    /* 清除bullet*/
    clean_bullet();
    /* 清除item*/
    clean_item();
    /* 清除explosion*/
    clean_explosion();
    /* 清理音效资源*/
    for (auto &sound : get_sounds())
    {
        if (sound.second != nullptr)
        {
            Mix_FreeChunk(sound.second);
        }
    }
    get_sounds().clear();
    /* 清理音频资源*/
    if (get_music() != nullptr)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(get_music());
        get_music() = nullptr;
    }
}
void MainScene::handle_event(SDL_Event *event)
{
    /* 处理fighter事件*/
    if (fighter)
    {
        fighter->handle_event(event);
    }
    /* 处理enemy事件*/
    for (auto &enemy : enemys)
    {
        enemy->handle_event(event);
    }
    /* 处理bullet事件*/
    for (auto &bullet : bullets)
    {
        bullet->handle_event(event);
    }
    /* 处理item事件*/
    for (auto &item : items)
    {
        item->handle_event(event);
    }
    /* 处理explosion事件*/
    for (auto &explosion : explosions)
    {
        explosion->handle_event(event);
    }
    /* 处理hud_manager事件*/
    get_game().get_hud().handle_event(event);
}
void MainScene::keyboard_ctrl()
{
    /* 状态查询获取当前的键盘状态*/
    const uint8_t *keyboard_state = SDL_GetKeyboardState(nullptr);
    if (fighter)
    {
        if (keyboard_state[SDL_SCANCODE_W])
        {
            /* 控制fighter*/
            fighter->get_point().y -= fighter->get_speed() * get_game().get_speedArg();
            /* 限制fighter移动范围*/
            if (fighter->get_point().y <= 0)
            {
                fighter->get_point().y = 0;
            }
        }
        if (keyboard_state[SDL_SCANCODE_A])
        {
            /* 控制fighter*/
            fighter->get_point().x -= fighter->get_speed() * get_game().get_speedArg();
            /* 限制fighter移动范围*/
            if (fighter->get_point().x <= 0)
            {
                fighter->get_point().x = 0;
            }
        }
        if (keyboard_state[SDL_SCANCODE_S])
        {
            /* 控制fighter*/
            fighter->get_point().y += fighter->get_speed() * get_game().get_speedArg();
            /* 限制fighter移动范围*/
            if (fighter->get_point().y >= (get_game().get_height() - fighter->get_height()))
            {
                fighter->get_point().y = (get_game().get_height() - fighter->get_height());
            }
        }
        if (keyboard_state[SDL_SCANCODE_D])
        {
            /* 控制fighter*/
            fighter->get_point().x += fighter->get_speed() * get_game().get_speedArg();
            /* 限制fighter移动范围*/
            if (fighter->get_point().x >= (get_game().get_width() - fighter->get_width()))
            {
                fighter->get_point().x = (get_game().get_width() - fighter->get_width());
            }
        }
        if (keyboard_state[SDL_SCANCODE_SPACE])
        {
            /* fighter射击bullet(参数固定是nullptr)*/
            auto bullet = fighter->shoot_bullet(nullptr, fighter->get_damage());
            if (bullet != nullptr)
            {
                bullets.push_back(std::move(bullet));
                /* 播放音效*/
                auto chunk = get_sounds().at(SPACESHOOT_FIGHTER_SHOOT_SOUND_KEY);
                Mix_PlayChannel(0, chunk, 0);
            }
        }
    }
}
void MainScene::create_enemy()
{
    /* 平均1s生成一个enemy*/
    if (get_game().random() > 1.0f / (float)(get_game().get_fps()))
    {
        return;
    }
    /* 等概率生成不同类型*/
    const float enemy_random = get_game().random();
    Enemy::EnemyType type = Enemy::EnemyType::None;
    const int max_index = static_cast<int>(Enemy::EnemyType::EnemyTypeMax);
    if (enemy_random < 1.0 / (float)(max_index - 1))
    {
        type = Enemy::EnemyType::HAJI_1;
    }
    else
    {
        type = Enemy::EnemyType::MANBO;
    }
    /* 创建一个enemy智能指针*/
    auto enemy = std::make_unique<Enemy>(type);
    /* 初始化enemy*/
    enemy->init();
    /* 定位enemy的水平坐标(随机生成)*/
    enemy->get_point().x = get_game().random() * (get_game().get_width() - enemy->get_width());
    /* 定位enemy的垂直坐标(设置在屏幕上方)*/
    enemy->get_point().y = -(float)(enemy->get_height());
    /* 添加到数组中*/
    enemys.push_back(std::move(enemy));
}
void MainScene::update_fighter()
{
    if (fighter)
    {
        if (fighter->get_dead())
        {
            fighter->clean();
            /* 销毁对象并滞空指针*/
            fighter.reset();
        }
        else
        {
            fighter->update();
        }
    }
}
void MainScene::update_bkScroller()
{
    nearStar->update();
    farStar->update();
}
void MainScene::update_enemy()
{
    for (auto it = enemys.begin(); it != enemys.end();)
    {
        if ((*it)->get_dead())
        {
            /* 清除enemy资源*/
            (*it)->clean();
            /* 删除当前enemy*/
            it = enemys.erase(it);
        }
        else
        {
            /* enemy射击*/
            if (fighter)
            {
                auto bullet = (*it)->shoot_bullet(fighter.get(), (*it)->get_damage());
                if (bullet)
                {
                    bullets.push_back(std::move(bullet));
                    auto chunk = get_sounds().at(SPACESHOOT_ENEMY_SHOOT_SOUND_KEY);
                    Mix_PlayChannel(-1, chunk, 0);
                }
            }
            (*it)->update();
            it++;
        }
    }
}
void MainScene::update_bullet()
{
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        /* bullet越界*/
        if ((*it)->get_dead())
        {
            /* 清除bullet资源*/
            (*it)->clean();
            /* 删除当前bullet*/
            it = bullets.erase(it);
        }
        else
        {
            switch ((*it)->get_type())
            {
            /* 避免编译警告*/
            case Bullet::BulletType::BulletTypeMax:
            case Bullet::BulletType::None:
                /* nothing to do*/
                break;
            case Bullet::BulletType::Fighter:
                /* enemy击中检测*/
                for (auto &enemy : enemys)
                {
                    if (bullet_collisionDetection((*it).get(), enemy.get()))
                    {
                        auto hit_chunk = get_sounds().at(SPACESHOOT_HIT_SOUND_SOUND_KEY);
                        Mix_PlayChannel(-1, hit_chunk, 0);
                        if (enemy->get_dead())
                        {
                            /* 爆炸效果*/
                            auto explosion = enemy->explode();
                            explosions.push_back(std::move(explosion));
                            auto chunk = get_sounds().at(SPACESHOOT_ENEMY_EXPLODE_SOUND_KEY);
                            Mix_PlayChannel(-1, chunk, 0);
                            /* 更新分数*/
                            if (fighter)
                            {
                                fighter->get_score() += 10;
                            }
                            /* 掉落item(25%概率)*/
                            if (get_game().random() < 0.25f)
                            {
                                auto item = enemy->drop_item();
                                items.push_back(std::move(item));
                            }
                        }
                        break;
                    }
                }
                break;
            case Bullet::BulletType::Enemy:
                /* fighter击中检测*/
                if (fighter)
                {
                    if (bullet_collisionDetection((*it).get(), fighter.get()))
                    {
                        auto hit_chunk = get_sounds().at(SPACESHOOT_HIT_SOUND_SOUND_KEY);
                        Mix_PlayChannel(-1, hit_chunk, 0);
                        /* 爆炸效果*/
                        if (fighter->get_dead())
                        {
                            auto explosion = fighter->explode();
                            explosions.push_back(std::move(explosion));
                            auto chunk = get_sounds().at(SPACESHOOT_FIGHTER_EXPLODE_SOUND_KEY);
                            Mix_PlayChannel(-1, chunk, 0);
                        }
                    }
                }
                break;
            }
            (*it)->update();
            it++;
        }
    }
}
void MainScene::update_item()
{
    for (auto it = items.begin(); it != items.end();)
    {
        if ((*it)->get_dead())
        {
            (*it)->clean();
            it = items.erase(it);
        }
        else
        {
            /* 碰撞检测*/
            if (fighter)
            {
                if (item_collisionDetection((*it).get(), fighter.get()))
                {
                    /* fighter获取item*/
                    fighter->get_item((*it).get());
                    auto chunk = get_sounds().at(SPACESHOOT_FIGHTER_BONUS_SOUND_KEY);
                    Mix_PlayChannel(-1, chunk, 0);
                }
            }
            (*it)->update();
            it++;
        }
    }
}
void MainScene::update_explosion()
{
    for (auto it = explosions.begin(); it != explosions.end();)
    {
        if ((*it)->get_finish())
        {
            (*it)->clean();
            it = explosions.erase(it);
        }
        else
        {
            (*it)->update();
            it++;
        }
    }
}
void MainScene::update_hudManager()
{
    /* 更新hud_state*/
    if (fighter)
    {
        hud_state.total_health = fighter->get_health();
        hud_state.current_health = fighter->get_curHealth();
        hud_state.score = fighter->get_score();
    }
    /* 更新hud_manager*/
    get_game().get_hud().update(hud_state);
}
void MainScene::render_fighter()
{
    if (fighter)
    {
        fighter->render();
    }
}
void MainScene::render_bkScroller()
{
    if (nearStar)
    {
        nearStar->render();
    }
    if (farStar)
    {
        farStar->render();
    }
}
void MainScene::render_enemy()
{
    for (auto &enemy : enemys)
    {
        enemy->render();
    }
}
void MainScene::render_bullet()
{
    for (auto &bullet : bullets)
    {
        bullet->render();
    }
}
void MainScene::render_item()
{
    for (auto &item : items)
    {
        item->render();
    }
}
void MainScene::render_explosion()
{
    for (auto &explosion : explosions)
    {
        explosion->render();
    }
}
void MainScene::render_hudManager()
{
    get_game().get_hud().render();
}
void MainScene::clean_fighter()
{
    if (fighter)
    {
        fighter->clean();
    }
}
void MainScene::clean_bkScroller()
{
    if (nearStar)
    {
        nearStar->clean();
    }
    if (farStar)
    {
        farStar->clean();
    }
}
void MainScene::clean_enemy()
{
    for (auto &enemy : enemys)
    {
        enemy->clean();
    }
    enemys.clear();
}
void MainScene::clean_bullet()
{
    for (auto &bullet : bullets)
    {
        bullet->clean();
    }
    bullets.clear();
}
void MainScene::clean_item()
{
    for (auto &item : items)
    {
        item->clean();
    }
    items.clear();
}
void MainScene::clean_explosion()
{
    for (auto &explosion : explosions)
    {
        explosion->clean();
    }
    explosions.clear();
}
/**
 * @brief: 子弹击中检测函数
 * @return: true: obj被击中, false: obj没被击中
 */
bool MainScene::bullet_collisionDetection(Bullet *bullet, GameObject *obj)
{
    if (obj->get_dead())
    {
        /* 对象死亡，则跳过击中检测*/
        return false;
    }
    SDL_Rect Bullet_rect{
        static_cast<int>(bullet->get_point().x),
        static_cast<int>(bullet->get_point().y),
        bullet->get_width(),
        bullet->get_height()};
    SDL_Rect Object_rect{
        static_cast<int>(obj->get_point().x),
        static_cast<int>(obj->get_point().y),
        obj->get_width(),
        obj->get_height()};
    if (SDL_HasIntersection(&Bullet_rect, &Object_rect))
    {
        /* 一枚子弹只能击中一个对象*/
        bullet->get_dead() = true;
        /* 血量扣除*/
        obj->get_curHealth() -= bullet->get_damage();
        /* 血量检测*/
        if (obj->get_curHealth() <= 0)
        {
            /* dead标志*/
            obj->get_dead() = true;
        }
        return true;
    }
    return false;
}
/**
 * @brief: 物品碰撞检测函数
 * @return: true: 碰撞, false: 没碰撞
 */
bool MainScene::item_collisionDetection(Item *item, GameObject *obj)
{
    if (obj->get_dead())
    {
        /* 对象死亡，则跳过碰撞检测*/
        return false;
    }
    SDL_Rect Item_rect{
        static_cast<int>(item->get_point().x),
        static_cast<int>(item->get_point().y),
        item->get_width(),
        item->get_height()};
    SDL_Rect Object_rect{
        static_cast<int>(obj->get_point().x),
        static_cast<int>(obj->get_point().y),
        obj->get_width(),
        obj->get_height()};
    if (SDL_HasIntersection(&Item_rect, &Object_rect))
    {
        item->get_dead() = true;
        return true;
    }
    return false;
}
