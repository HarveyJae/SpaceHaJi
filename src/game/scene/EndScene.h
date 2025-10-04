#pragma once
#include "Scene.h"
#include "HudState.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <map>
class EndScene : public Scene
{
private:
    /* 玩家名称*/
    std::string name;
    /* 正在输入标志*/
    bool typing_flag = false;
    /* HudState对象*/
    HudState hud_state;
    /* 控制字符闪烁的定时器*/
    uint32_t timer = 0;
    /* 分数排行榜(按分数排名)*/
    std::multimap<int, std::string, std::greater<int>> rank_board;
    /* 私有方法*/
    void render_textTyping();
    void render_rankBoard();
    void remove_lastUTF8Char(std::string& str);
    void insert_rankBoard(int score, std::string name);
public:
    EndScene();
    ~EndScene();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
