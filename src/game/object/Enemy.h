#pragma once
#include "GameObject.h"

#define SPACESHOOT_OBJECT_ENEMY_IMAGE_PATH "../assets/image/insect-1.png" /* enemy图片路径*/
#define SPACESHOOT_ENEMY_DEFAULT_SPEED 200                                /* enemy的速度，200px/s*/
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
