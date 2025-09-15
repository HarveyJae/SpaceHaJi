#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "GameManager.h"
#define jjj 1
class MainScene : public Scene
{
private:
    GameManager &game;
    Fighter fighter;
public:
    MainScene();
    ~MainScene();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;

    /* 键盘控制函数*/
    void keyboard_ctrl();
};
