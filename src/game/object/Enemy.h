#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
private:
public:
    Enemy();
    ~Enemy();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
