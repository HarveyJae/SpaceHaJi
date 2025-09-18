#include "MainScene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
#include <memory>
#include <vector>
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
