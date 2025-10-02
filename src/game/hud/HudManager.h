#pragma once
#include "SDL.h"
#include "HudState.h"
#include "SDL_ttf.h"
#include <string>
class GameManager;
class HudManager
{
private:
    GameManager &game;
    /* hud state*/
    HudState state;
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
    void update(HudState &state);
    void render();
    void clean();
    void handle_event(SDL_Event *event);
};
