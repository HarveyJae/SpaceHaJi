#include "TitleScene.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "GameManager.h"
#include "HudManager.h"
#include "HudState.h"
#include "MainScene.h"
#include <iostream>
#define SPACESHOOT_TITLESCENE_MUSIC_PATH "../assets/music/deadjimi.mp3"                    /* titlescene的背景音乐路径*/
#define SPACESHOOT_TITLESCENE_TITLE_TEXT_FONT_PATH "../assets/font/VonwaonBitmap-16px.ttf" /* title_text字体路径*/
#define SPACESHOOT_TITLESCENE_TITLE_TEXT_FONT_SIZE 64                                      /* title_text字体大小*/
#define SPACESHOOT_TITLESCENE_FLASH_TEXT_FONT_PATH "../assets/font/VonwaonBitmap-16px.ttf" /* flash_text字体路径*/
#define SPACESHOOT_TITLESCENE_FLASH_TEXT_FONT_SIZE 32                                      /* flash_text字体大小*/
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
        std::cout << "TitleScene music load failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    Mix_PlayMusic(get_music(), -1);
    /* 初始化title_text*/
    titleText_font = TTF_OpenFont(SPACESHOOT_TITLESCENE_TITLE_TEXT_FONT_PATH, SPACESHOOT_TITLESCENE_TITLE_TEXT_FONT_SIZE);
    if (!titleText_font)
    {
        std::cout << "Load title text font failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 初始化flash_text*/
    flashText_font = TTF_OpenFont(SPACESHOOT_TITLESCENE_FLASH_TEXT_FONT_PATH, SPACESHOOT_TITLESCENE_FLASH_TEXT_FONT_SIZE);
    if (!flashText_font)
    {
        std::cout << "Load flash text font failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
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
    SDL_Surface *title_surface = TTF_RenderUTF8_Solid(titleText_font, title_text.c_str(), titleText_color);
    if (!title_surface)
    {
        return;
    }
    SDL_Texture *title_texture = SDL_CreateTextureFromSurface(get_game().get_renderer(), title_surface);
    titleText_Point.x = get_game().get_width() / 2 - title_surface->w / 2;
    titleText_Point.y = static_cast<int>((get_game().get_height() - title_surface->h) * 0.3f);
    SDL_Rect title_rect{titleText_Point.x, titleText_Point.y, title_surface->w, title_surface->h};
    SDL_RenderCopy(get_game().get_renderer(), title_texture, nullptr, &title_rect);
    SDL_DestroyTexture(title_texture);
    SDL_FreeSurface(title_surface);
    /* 渲染闪烁文字*/
    std::string flash_text = "按 J 键开始游戏";
    SDL_Surface *flash_surface = TTF_RenderUTF8_Solid(flashText_font, flash_text.c_str(), flashText_color);
    if (!flash_surface)
    {
        return;
    }
    SDL_Texture *flash_texture = SDL_CreateTextureFromSurface(get_game().get_renderer(), flash_surface);
    flashText_Point.x = get_game().get_width() / 2 - flash_surface->w / 2;
    flashText_Point.y = static_cast<int>((get_game().get_height() - flash_surface->h) * 0.7f);
    SDL_Rect flash_rect{flashText_Point.x, flashText_Point.y, flash_surface->w, flash_surface->h};
    /* 0.5s闪烁一次*/
    if (timer < 500)
    {
        SDL_RenderCopy(get_game().get_renderer(), flash_texture, nullptr, &flash_rect);
        SDL_DestroyTexture(flash_texture);
        SDL_FreeSurface(flash_surface);
    }
}
void TitleScene::clean()
{
    if (titleText_font)
    {
        TTF_CloseFont(titleText_font);
        titleText_font = nullptr;
    }
    if (flashText_font)
    {
        TTF_CloseFont(flashText_font);
        flashText_font = nullptr;
    }
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