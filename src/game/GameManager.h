#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__
#include "Scene.h"
#define SPACESHOOT_WINDOW_WIDTH_PX 600            /* 游戏窗口宽度*/
#define SPACESHOOT_WINDOW_HEIGHT_PX 800           /* 游戏窗口高度*/
#define SPACESHOOT_WINDOW_TITLE_NAME "spaceshoot" /* 游戏窗口名称*/
/**
 * @brief: 游戏的主类，管理游戏循环和场景切换
 */
class GameManager
{
private:
    bool running_flag = false;                /* 游戏运行标志*/
    Scene *current_scene = nullptr;           /* 当前活动场景*/
    int width = SPACESHOOT_WINDOW_WIDTH_PX;   /* 窗口宽度*/
    int height = SPACESHOOT_WINDOW_HEIGHT_PX; /* 窗口高度*/
    SDL_Window *window = nullptr;             /* 窗口*/
    SDL_Renderer *renderer = nullptr;         /* 渲染器*/

public:
    GameManager();
    ~GameManager();
    void init();                         /* 初始化游戏*/
    void run();                          /* 运行游戏资源*/
    void clean();                        /* 清理游戏资源*/
    void change_scene(Scene *scene);     /* 切换游戏场景*/
    void update();                       /* 更新游戏资源*/
    void render();                       /* 渲染*/
    void handle_event(SDL_Event *event); /* 事件处理*/
};

#endif