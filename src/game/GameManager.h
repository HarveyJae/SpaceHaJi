#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__
#include "Scene.h"
/**
 * @brief: 游戏的主类，管理游戏循环和场景切换
 */
class GameManager
{
private:
    bool running_flag = false;      /* 游戏运行标志*/
    Scene *current_scene = nullptr; /* 当前活动场景*/
public:
    GameManager(/* args */);
    ~GameManager();
    void init();                     /* 初始化游戏*/
    void run();                      /* 运行游戏资源*/
    void clean();                    /* 清理游戏资源*/
    void change_scene(Scene *scene); /* 切换游戏场景*/
};

#endif