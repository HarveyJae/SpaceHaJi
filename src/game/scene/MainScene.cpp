#include "MainScene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
#include <memory>
#include <vector>
#include <random>
MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}
void MainScene::init()
{
    /* 初始化fighter对象*/
    fighter.init();
    /* 获取随机数种子*/
    std::random_device rd;
    /* 初始化随机数分配器*/
    gen = std::mt19937(rd());
    /* 初始化随机数分布器*/
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
}
void MainScene::update()
{
    /* 场景键盘操作*/
    keyboard_ctrl();
    /* 更新fighter帧*/
    update_fighter();
    /* 按既定概率创建enemy*/
    create_enemy();
    /* 更新enemy*/
    update_enemy();
    /* 更新bullet*/
    update_bullet();
    /* 更新explosion*/
    update_explosion();
}
void MainScene::render()
{
    /* 绘制fighter帧*/
    render_fighter();
    /* 绘制enemy*/
    render_enemy();
    /* 绘制bullet*/
    render_bullet();
    /* 绘制explosion*/
    render_explosion();
}
void MainScene::clean()
{
    /* 清除fighter*/
    clean_fighter();
    /* 清除enemy*/
    clean_enemy();
    /* 清除bullet*/
    clean_bullet();
    /* 清除explosion*/
    clean_explosion();
}
void MainScene::handle_event(SDL_Event *event)
{
    /* 处理fighter事件*/
    fighter.handle_event(event);
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
    /* 处理explosion事件*/
    for (auto &explosion : explosions)
    {
        explosion->handle_event(event);
    }
}
void MainScene::keyboard_ctrl()
{
    /* 状态查询获取当前的键盘状态*/
    const uint8_t *keyboard_state = SDL_GetKeyboardState(nullptr);
    if (keyboard_state[SDL_SCANCODE_W])
    {
        /* 控制fighter*/
        fighter.get_point().y -= fighter.get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (fighter.get_point().y <= 0)
        {
            fighter.get_point().y = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_A])
    {
        /* 控制fighter*/
        fighter.get_point().x -= fighter.get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (fighter.get_point().x <= 0)
        {
            fighter.get_point().x = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        /* 控制fighter*/
        fighter.get_point().y += fighter.get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (fighter.get_point().y >= (get_game().get_height() - fighter.get_height()))
        {
            fighter.get_point().y = (get_game().get_height() - fighter.get_height());
        }
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        /* 控制fighter*/
        fighter.get_point().x += fighter.get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (fighter.get_point().x >= (get_game().get_width() - fighter.get_width()))
        {
            fighter.get_point().x = (get_game().get_width() - fighter.get_width());
        }
    }
    if (keyboard_state[SDL_SCANCODE_SPACE])
    {
        /* fighter射击bullet(参数固定是nullptr)*/
        auto bullet = fighter.shoot_bullet(nullptr, fighter.get_damage());
        if (bullet != nullptr)
        {
            bullets.push_back(std::move(bullet));
        }
    }
}
void MainScene::create_enemy()
{
    /* 平均1s生成一个enemy*/
    if (dis(gen) > 1.0f / (float)(get_game().get_fps()))
    {
        return;
    }
    /* 创建一个enemy智能指针*/
    auto enemy = std::make_unique<Enemy>();
    /* 初始化enemy*/
    enemy->init();
    /* 定位enemy的水平坐标(随机生成)*/
    enemy->get_point().x = dis(gen) * (get_game().get_width() - enemy->get_width());
    /* 定位enemy的垂直坐标(设置在屏幕上方)*/
    enemy->get_point().y = -(float)(enemy->get_height());
    /* 添加到数组中*/
    enemys.push_back(std::move(enemy));
}
void MainScene::update_fighter()
{
    if (fighter.get_dead())
    {
        fighter.clean();
        fighter.get_cleanFlag() = true;
    }
    else
    {
        fighter.update();
    }
}
/**
 * @todo: 在update里面添加碰撞检测
 */
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
            /* 删除时会返回下一个迭代器，只有不删除时才更新*/
            /* enemy射击*/
            auto bullet = (*it)->shoot_bullet(&fighter, (*it)->get_damage());
            if (bullet != nullptr)
            {
                bullets.push_back(std::move(bullet));
            }
            /* 更新enemy*/
            (*it)->update();
            it++;
        }
    }
}
void MainScene::update_bullet()
{
    /* 更新bullet*/
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
            /* 更新bullet*/
            (*it)->update();
            /* 子弹越界死亡判断*/
            if ((*it)->get_dead())
            {
                /* 清除bullet资源*/
                (*it)->clean();
                /* 删除当前bullet*/
                it = bullets.erase(it);
                continue;
            }
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
                        /* 爆炸效果*/
                        if (enemy->get_dead())
                        {
                            auto explosion = enemy->explode();
                            explosions.push_back(std::move(explosion));
                        }
                        break;
                    }
                }
                break;
            case Bullet::BulletType::Enemy:
                /* fighter击中检测*/
                if (bullet_collisionDetection((*it).get(), &fighter))
                {
                    /* 爆炸效果*/
                    if (fighter.get_dead())
                    {
                        auto explosion = fighter.explode();
                        explosions.push_back(std::move(explosion));
                    }
                }
                break;
            }
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
void MainScene::render_fighter()
{
    fighter.render();
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
void MainScene::render_explosion()
{
    for (auto &explosion : explosions)
    {
        explosion->render();
    }
}
void MainScene::clean_fighter()
{
    if (!fighter.get_cleanFlag())
    {
        fighter.clean();
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
    if(obj->get_dead())
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
