#pragma once
#include "GameEffect.h"
class Explosion : public GameEffect
{
private:
public:
    Explosion();
    ~Explosion() override;
    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handle_event(SDL_Event *event) override;
};
