#include "TitleScene.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "GameManager.h"
#include <iostream>
#define SPACESHOOT_TITLESCENE_MUSIC_PATH "../assets/music/06_Battle_in_Space_Intro.ogg" /* titlescene的背景音乐路径*/
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}
void TitleScene::init()
{
    /* 初始化音频*/
    get_music() = Mix_LoadMUS(SPACESHOOT_TITLESCENE_MUSIC_PATH);
    if (!get_music())
    {
        std::cout << "TitleScene music load failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(get_music(), -1);
    /* 初始化计时器*/
    timer = 0;
}
void TitleScene::update()
{
    /* 更新计时器(循环计时1000ms)*/
    timer += get_game().get_frameTime();
    if (timer >= 1000)
    {
        timer = 0;
    }
}
void TitleScene::render()
{
    // /* 渲染标题文字*/
    // std::string title_text = "太空哈基咪";
    // game.renderTextCentered(title_text, 0.4, true);
    // /* 渲染普通文字*/
    // if (timer < 0.5f)
    // {
    //     std::string instructions = "按 J 键开始游戏";
    //     game.renderTextCentered(instructions, 0.8, false);
    // }
}
void TitleScene::clean()
{
}
void TitleScene::handle_event(SDL_Event *event)
{
}