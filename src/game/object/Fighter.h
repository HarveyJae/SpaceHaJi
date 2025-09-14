#pragma once
#include "GameObject.h"
class Fighter : public GameObject
{
private:
public:
    Fighter();
    ~Fighter();
    void init() override;
    void update() override;
    void render() override;
    void handle_event(SDL_Event *event) override;
};


