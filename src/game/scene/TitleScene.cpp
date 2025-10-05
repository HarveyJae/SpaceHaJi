#include "TitleScene.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "GameManager.h"
#include "HudManager.h"
#include "HudState.h"
#include "MainScene.h"
#include <iostream>
#define SPACESHOOT_TITLESCENE_MUSIC_PATH "../assets/music/deadjimi.mp3"                    /* titlescene的背景音乐路径*/
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
void TitleScene::init()
{
    get_game().get_hud().set_sceneType(HudManager::HudSceneType::Title);
    /* 初始化音频*/
    get_music() = Mix_LoadMUS(SPACESHOOT_TITLESCENE_MUSIC_PATH);
    if (!get_music())
    {
        std::cerr << "TitleScene music load failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(get_music(), -1);
    /* 初始化计时器*/
    timer = 0;
}
void TitleScene::update()
{
    get_game().get_hud().update(hud_state);
    /* 更新计时器(循环计时1000ms)*/
    timer += get_game().get_frameTime();
    if (timer >= 1000)
    {
        timer = 0;
    }
}
void TitleScene::render()
{
    /* 渲染hud*/
    get_game().get_hud().render();
    /* 渲染标题文字*/
    std::string title_text = "太空哈基咪";
    SDL_Color title_color{255, 255, 255, 255};
    get_game().RenderTextCenterW(title_text, GameManager::NormalFontType::Large, title_color, 0.3);
    /* 渲染闪烁文字*/
    std::string flash_text = "按 J 键开始游戏";
    SDL_Color flash_color{255, 255, 255, 255};
    /* 0.5s闪烁一次*/
    if (timer < 500)
    {
        get_game().RenderTextCenterW(flash_text, GameManager::NormalFontType::Medium, flash_color, 0.7);
    }
}
void TitleScene::clean()
{
    /* nothing to do*/
}
void TitleScene::handle_event(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.scancode == SDL_SCANCODE_J)
        {
            get_game().change_sceneNow(std::make_unique<MainScene>());
        }
    }
}