#pragma once
#include "GameObject.h"
#define SPACESHOOT_OBJECT_BULLET_IMAGE_PATH "../assets/image/bullet.png" /* bullet图片路径*/
#define SPACESHOOT_BULLET_DEFAULT_SPEED 400                              /* bullet的速度，400px/s*/

class Bullet : public GameObject
{
private:
public:
    Bullet();
    ~Bullet();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
