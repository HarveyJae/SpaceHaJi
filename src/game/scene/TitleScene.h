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
