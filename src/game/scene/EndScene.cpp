#include "EndScene.h"
#include "GameManager.h"
#include "HudManager.h"
#include "HudState.h"
#include <iostream>

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}
void EndScene::init()
{
    /* 设置hud类型*/
    get_game().get_hud().set_sceneType(HudManager::HudSceneType::End);
    /* 开启文本输入功能*/
    if (!SDL_IsTextInputActive())
    {
        SDL_StartTextInput();
    }
    if (!SDL_IsTextInputActive())
    {
        std::cout << "EndScene text input open failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 开启输入标志*/
    typing_flag = true;
}
void EndScene::update()
{
}
void EndScene::render()
{
    /* 渲染hud*/
    get_game().get_hud().render();
    /* 渲染结束文字*/
    render_textTyping();
}
void EndScene::clean()
{
    /* nothing to do.*/
}
void EndScene::handle_event(SDL_Event *event)
{
    if (typing_flag) /* 玩家名称输入*/
    {
        if (event->type == SDL_TEXTINPUT)
        {
            name += event->text.text;
        }
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                typing_flag = false;
                SDL_StopTextInput();
            }
            if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
            {
                if (!name.empty())
                {
                    removeLastUTF8Char(name);
                }
            }
        }
    }
    else /* 排行榜*/
    {
    }
}
void EndScene::render_textTyping()
{
    /* 渲染结束文字*/
    hud_state = get_game().get_hud().get_hudState();
    SDL_Color color{255, 255, 255, 255};
    std::string text;
    text = "你的得分是: " + std::to_string(hud_state.score);
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Small, color, 0.3);
    text = "Game Over";
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Medium, color, 0.4);
    text = "请输入你的名字, 按回车键退出: ";
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Small, color, 0.5);

    /* 渲染用户输入名称*/
    if (!name.empty())
    {
        get_game().RenderTextCenterW(name, GameManager::NormalFontType::Small, color, 0.6);
    }
}
void EndScene::render_rank()
{
}
/**
 * @brief: 正确退格utf-8字符
 */
void EndScene::removeLastUTF8Char(std::string &str)
{
    auto lastchar = str.back();
    if ((lastchar & 0b10000000) == 0b10000000)
    {
        str.pop_back();
        while ((str.back() & 0b11000000) != 0b11000000)
        {
            str.pop_back();
        }
    }
    str.pop_back();
}