#pragma once
#include "SDL.h"
#include "HudState.h"
#include "SDL_ttf.h"
#include <string>
#include <memory>
class GameManager;
class BkScroller;
class HudManager
{
public:
    enum class HudSceneType
    {
        None,
        Title,
        Main,
        End,
        HudSceneTypeMax,
    };

private:
    GameManager &game;
    /* 场景类型(决定render)*/
    HudSceneType scene_type = HudSceneType::None;
    /* hud state*/
    HudState state;
    /* BkScroller_hud属性*/
    std::unique_ptr<BkScroller> nearStar;
    std::unique_ptr<BkScroller> farStar;
    /* health_hud属性*/
    SDL_Texture *health_texture = nullptr;
    int health_width = 0;
    int health_height = 0;
    SDL_Point health_startPoint{0, 0};
    int health_offset = 0;
    /* score_hud属性*/
    TTF_Font *score_font = nullptr;
    std::string score_text;
    SDL_Color score_color{255, 255, 255, 255};
    SDL_Point score_startPoint{0, 0};
    /* BkScroller_hud方法*/
    void init_BkScrollerHud();
    void update_BkScrollerHud();
    void render_BkScrollerHud();
    void clean_BkScrollerHud();
    /* health_hud方法*/
    void init_healthHud();
    void update_healthHud();
    void render_healthHud();
    void clean_healthHud();
    /* score_hud方法*/
    void init_scoreHud();
    void update_scoreHud();
    void render_scoreHud();
    void clean_scoreHud();

public:
    HudManager();
    ~HudManager();
    void init();
    void update(const HudState &hud_state);
    void render();
    void clean();
    void handle_event(SDL_Event *event);

    /* 辅助函数*/
    void set_sceneType(HudSceneType type);
};
