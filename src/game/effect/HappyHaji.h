#pragma once
#include "GameEffect.h"
class HappyHaji : public GameEffect
{
private:
public:
    HappyHaji();
    ~HappyHaji();
    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handle_event(SDL_Event *event) override;
};
