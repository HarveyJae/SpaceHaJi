#pragma once
#include "GameEffect.h"
#define SPACESHOOT_EFFECT_EXPLOSION_IMAGE_PATH "../assets/effect/explosion.png" /* explosion图片路径*/
#define SPACESHOOT_EXPLOSION_DEFAULT_FPS 10                                     /* explosion的帧率，10fps*/
#define SPACESHOOT_EXPLOSION_DEFAULT_TOTAL_FRAME 9                              /* explosion的帧数，9 frame*/

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
