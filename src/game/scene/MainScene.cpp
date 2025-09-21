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
    /* 在射击的时候初始化bullet对象*/
    /* 在enemy生成函数中初始化enemy对象*/
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
    fighter.update();
    /* 更新bullet数组(用迭代器更新，方便清除)*/
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if ((*it)->get_dead())
        {
            /* 清除bullet资源*/
            (*it)->clean();
            /* 删除当前bullet*/
            it = bullets.erase(it);
        }
        else
        {
            /* 删除时会返回下一个迭代器，只有不删除时才更新*/
            (*it)->update();
            it++;
        }
    }
    /* 创建enemy*/
    create_enemy();
    /* 更新bullet数组(用迭代器更新，方便清除)*/
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
            (*it)->update();
            it++;
        }
    }
}
void MainScene::render()
{
    /* 绘制fighter帧*/
    fighter.render();
    /* 绘制bullet数组*/
    for (auto &bullet : bullets)
    {
        bullet->render();
    }
    /* 绘制enemy数组*/
    for (auto &enemy : enemys)
    {
        enemy->render();
    }
}
void MainScene::clean()
{
    /* 清除fighter对象*/
    fighter.clean();
    /* 清理bullet数组*/
    for (auto &bullet : bullets)
    {
        bullet->clean();
    }
    bullets.clear();
    /* 清理enemy数组*/
    for (auto &enemy : enemys)
    {
        enemy->clean();
    }
    enemys.clear();
}
void MainScene::handle_event(SDL_Event *event)
{
    /* 处理fighter事件*/
    fighter.handle_event(event);
    /* 处理bullet事件*/
    for (auto &bullet : bullets)
    {
        bullet->handle_event(event);
    }
    /* 处理enemy事件*/
    for (auto &enemy : enemys)
    {
        enemy->handle_event(event);
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
        /* 射击bullet*/
        auto bullet = fighter.shoot_bullet();
        if (bullet)
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