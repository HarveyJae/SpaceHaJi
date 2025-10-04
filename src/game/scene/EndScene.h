#pragma once
#include "Scene.h"
#include "HudState.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
class EndScene : public Scene
{
private:
    /* 玩家名称*/
    std::string name;
    /* 正在输入标志*/
    bool typing_flag = false;
    /* HudState对象*/
    HudState hud_state;

    /* 私有方法*/
    void render_textTyping();
    void render_rank();
    void removeLastUTF8Char(std::string& str);

public:
    EndScene();
    ~EndScene();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
