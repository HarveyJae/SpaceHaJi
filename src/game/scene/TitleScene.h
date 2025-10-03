#pragma once
#include "Scene.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "HudState.h"
class TitleScene : public Scene
{
private:
    /* HudState对象*/
    HudState hud_state;
    /* 标题文字*/
    TTF_Font *titleText_font = nullptr;
    SDL_Color titleText_color{255, 255, 255, 255};
    SDL_Point titleText_Point{0, 0};
    /* 闪烁文字*/
    TTF_Font *flashText_font = nullptr;
    SDL_Color flashText_color{255, 255, 255, 255};
    SDL_Point flashText_Point{0, 0};
    /* 计时器*/
    uint32_t timer = 0;

public:
    TitleScene();
    ~TitleScene();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
