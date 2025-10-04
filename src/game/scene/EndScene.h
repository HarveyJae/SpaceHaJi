#pragma once
#include "Scene.h"
class EndScene : public Scene
{
private:
    /* 跟踪游戏结束时间*/
    uint32_t timer = 0;

public:
    EndScene();
    ~EndScene();
};
