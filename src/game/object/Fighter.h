#pragma once
#include "GameObject.h"
#define SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH "../assets/image/SpaceShip.png" /* fighter图片路径*/
#define SPACESHOOT_FIGHTER_DEFAULT_SPEED 200                                 /* fighter的速度，200px/s*/

class Fighter : public GameObject
{
private:
    /* 键盘移动控制*/
    void keyboard_ctrl();

public:
    Fighter();
    ~Fighter();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
