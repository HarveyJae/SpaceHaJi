#pragma once
#include "Scene.h"
#include "SDL.h"
#include "HudState.h"
#include <memory>
class HappyHaji;
class TitleScene : public Scene
{
private:
    /* HudState对象*/
    HudState hud_state;
    /* 计时器*/
    uint32_t timer = 0;
    /* happy_haji对象*/
    std::unique_ptr<HappyHaji> happy_haji;
public:
    TitleScene();
    ~TitleScene();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
