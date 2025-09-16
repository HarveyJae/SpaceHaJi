#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"

class MainScene : public Scene
{
private:
    Fighter fighter;

public:
    MainScene();
    ~MainScene();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
