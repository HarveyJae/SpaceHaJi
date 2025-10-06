#pragma once
#include "GameObject.h"
#include <cstdint>
class Thruster : public GameObject
{
private:
    /* Thruster计时器*/
    uint32_t timer = 0;

public:
    Thruster();
    ~Thruster();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
