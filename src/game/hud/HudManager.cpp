#include "HudManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#include "HudState.h"
#define SPACESHOOT_HUD_HEALTH_IMAGE_PATH "../assets/image/health_hud.png" /* health_hud图片路径*/
HudManager::HudManager() : game(GameManager::getInstance())
{
}

HudManager::~HudManager()
{
}
void HudManager::init()
{
    init_healthHud();
}
void HudManager::update(HudState &state)
{
    this->state = state;
    update_healthHud();
}
void HudManager::render()
{
    render_healthHud();
}
void HudManager::clean()
{
    clean_healthHud();
}
void HudManager::handle_event(SDL_Event *event)
{
}
void HudManager::init_healthHud()
{
    /* 初始化health_hud*/
    health_hud = IMG_LoadTexture(game.get_renderer(), SPACESHOOT_HUD_HEALTH_IMAGE_PATH);
    SDL_QueryTexture(health_hud, nullptr, nullptr, &health_width, &health_height);
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
    SDL_SetTextureColorMod(health_hud, 255, 255, 255);
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
                SDL_SetTextureColorMod(health_hud, 100, 100, 100);
                color_cFlag = true;
            }   
        }
        SDL_RenderCopy(game.get_renderer(), health_hud, nullptr, &health_rect);
    }
}
void HudManager::clean_healthHud()
{
    /* 清除health_hud*/
    if (health_hud)
    {
        SDL_DestroyTexture(health_hud);
    }
}
