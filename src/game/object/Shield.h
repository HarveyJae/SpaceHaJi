#pragma once
#include "GameObject.h"
class Shield : public GameObject
{
private:
    /* shield计时器*/
    uint32_t timer = 0;
public:
    Shield();
    ~Shield();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
