#pragma once
#include "SDL.h"
#include "HudState.h"
class GameManager;
class HudManager
{
private:
    GameManager &game;
    /* hud state*/
    HudState state;
    /* health_hud属性*/
    SDL_Texture *health_hud;
    int health_width = 0;
    int health_height = 0;
    SDL_Point health_startPoint{0, 0};
    int health_offset = 0;
    void init_healthHud();
    void update_healthHud();
    void render_healthHud();
    void clean_healthHud();

public:
    HudManager();
    ~HudManager();
    void init();
    void update(HudState &state);
    void render();
    void clean();
    void handle_event(SDL_Event *event);
};
