#include "HudManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "GameManager.h"
#include "BkScroller.h"
#include "HudState.h"
#define SPACESHOOT_HUD_HEALTH_IMAGE_PATH "../assets/image/health_hud.png"      /* health_hud图片路径*/
#define SPACESHOOT_HUD_SCORE_FONT_PATH "../assets/font/VonwaonBitmap-12px.ttf" /* score_hud字体路径*/
#define SPACESHOOT_HUD_SCORE_FONT_SIZE 24                                      /* score_hud字体大小*/
#define SPACESHOOT_HUD_TITLE_FONT_PATH "../assets/font/VonwaonBitmap-16px.ttf" /* title_hud字体路径*/
#define SPACESHOOT_HUD_TITLE_FONT_SIZE 64                                      /* title_hud字体大小*/
HudManager::HudManager() : game(GameManager::getInstance())
{
}
HudManager::~HudManager()
{
}
/**
 * @brief: 禁止在场景中调用，只能在GameManager中调用
 */
void HudManager::init()
{
    init_BkScrollerHud();
    init_healthHud();
    init_scoreHud();
}
void HudManager::update(const HudState &hud_state)
{
    state = hud_state;
    update_BkScrollerHud();
    update_healthHud();
    update_scoreHud();
}
void HudManager::render()
{
    switch (scene_type)
    {
    /* 避免编译警告*/
    case HudSceneType::HudSceneTypeMax:
    case HudSceneType::None:
        /* nothing to do*/
        break;
    case HudSceneType::Title:
        render_BkScrollerHud();
        render_titleHud();
        break;
    case HudSceneType::Main:
        render_BkScrollerHud();
        render_healthHud();
        render_scoreHud();
        break;
    case HudSceneType::End:
        break;
    }
}
/**
 * @brief: 禁止在场景中调用，只能在GameManager中调用
 */
void HudManager::clean()
{
    clean_BkScrollerHud();
    clean_healthHud();
    clean_scoreHud();
    clean_titleHud();
}
void HudManager::handle_event(SDL_Event *event)
{
    switch (scene_type)
    {
    /* 避免编译警告*/
    case HudSceneType::HudSceneTypeMax:
    case HudSceneType::None:
        /* nothing to do*/
        break;
    case HudSceneType::Title:
        break;
    case HudSceneType::Main:
        break;
    case HudSceneType::End:
        break;
    }
}
void HudManager::init_BkScrollerHud()
{
    nearStar = std::make_unique<BkScroller>(BkScroller::BkScrollerType::NearStar);
    farStar = std::make_unique<BkScroller>(BkScroller::BkScrollerType::FarStar);
    nearStar->init();
    farStar->init();
}
void HudManager::update_BkScrollerHud()
{
    nearStar->update();
    farStar->update();
}
void HudManager::render_BkScrollerHud()
{
    nearStar->render();
    farStar->render();
}
void HudManager::clean_BkScrollerHud()
{
    nearStar->clean();
    farStar->clean();
}
void HudManager::init_healthHud()
{
    /* 初始化health_hud*/
    health_texture = IMG_LoadTexture(game.get_renderer(), SPACESHOOT_HUD_HEALTH_IMAGE_PATH);
    if (!health_texture)
    {
        std::cout << "Load health HUD texture failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(health_texture, nullptr, nullptr, &health_width, &health_height);
    /* 设置health_hud初始坐标*/
    health_startPoint.x = 10;
    health_startPoint.y = 10;
    /* 设置health_hud偏移像素值*/
    health_offset = 40;
}
void HudManager::update_healthHud()
{
    /* nothing to do*/
}
void HudManager::render_healthHud()
{
    SDL_SetTextureColorMod(health_texture, 255, 255, 255);
    /* 颜色衰减标志*/
    bool color_cFlag = false;
    /* 颜色非衰减*/
    for (int i = 0; i < state.total_health; i++)
    {
        SDL_Rect health_rect = {health_startPoint.x + i * health_offset, health_startPoint.y, health_width, health_height};
        if (i >= state.current_health)
        {
            /* 颜色衰减*/
            if (!color_cFlag)
            {
                SDL_SetTextureColorMod(health_texture, 100, 100, 100);
                color_cFlag = true;
            }
        }
        SDL_RenderCopy(game.get_renderer(), health_texture, nullptr, &health_rect);
    }
}
void HudManager::clean_healthHud()
{
    /* 清除health_hud*/
    if (health_texture)
    {
        SDL_DestroyTexture(health_texture);
        health_texture = nullptr;
    }
}
void HudManager::init_scoreHud()
{
    /* 初始化score_hud*/
    score_font = TTF_OpenFont(SPACESHOOT_HUD_SCORE_FONT_PATH, SPACESHOOT_HUD_SCORE_FONT_SIZE);
    if (!score_font)
    {
        std::cout << "Load score HUD font failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 设置score_hud初始坐标*/
    score_startPoint.x = 10;
    score_startPoint.y = health_height + 10;
}
void HudManager::update_scoreHud()
{
    /* nothing to do*/
}
void HudManager::render_scoreHud()
{
    score_text = "SCORE:" + std::to_string(state.score);
    SDL_Surface *score_surface = TTF_RenderUTF8_Solid(score_font, score_text.c_str(), score_color);
    if (!score_surface)
    {
        return;
    }
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(game.get_renderer(), score_surface);
    if (!score_texture)
    {
        SDL_FreeSurface(score_surface);
        return;
    }
    SDL_Rect score_rect{score_startPoint.x, score_startPoint.y, score_surface->w, score_surface->h};
    SDL_RenderCopy(game.get_renderer(), score_texture, nullptr, &score_rect);
    SDL_FreeSurface(score_surface);
    SDL_DestroyTexture(score_texture);
}
void HudManager::clean_scoreHud()
{
    if (score_font)
    {
        TTF_CloseFont(score_font);
        score_font = nullptr;
    }
}
void HudManager::init_titleHud()
{
    /* 初始化title_hud*/
    title_font = TTF_OpenFont(SPACESHOOT_HUD_TITLE_FONT_PATH, SPACESHOOT_HUD_TITLE_FONT_SIZE);
    if (!title_font)
    {
        std::cout << "Load title HUD font failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
}
void HudManager::update_titleHud()
{
    /* nothing to do*/
}
void HudManager::render_titleHud()
{
    /* 固定title*/
    title_text = "太空哈基咪";
    SDL_Surface *title_surface = TTF_RenderUTF8_Solid(title_font, title_text.c_str(), title_color);
    if (!title_surface)
    {
        return;
    }
    SDL_Texture *title_texture = SDL_CreateTextureFromSurface(game.get_renderer(), title_surface);
    title_Point.x = game.get_width() / 2 - title_surface->w / 2;
    title_Point.y = static_cast<int>((game.get_height() - title_surface->h) * 0.4f);
    SDL_Rect title_rect{title_Point.x, title_Point.y, title_surface->w, title_surface->h};
    SDL_RenderCopy(game.get_renderer(), title_texture, nullptr, &title_rect);
    SDL_DestroyTexture(title_texture);
    SDL_FreeSurface(title_surface);
}
void HudManager::clean_titleHud()
{
    if (title_font)
    {
        TTF_CloseFont(title_font);
        title_font = nullptr;
    }
}
void HudManager::set_sceneType(HudSceneType type)
{
    /* 类型越界检测*/
    if (type < HudSceneType::None || type >= HudSceneType::HudSceneTypeMax)
    {
        type = HudSceneType::None;
    }
    scene_type = type;
}