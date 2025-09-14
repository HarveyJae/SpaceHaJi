#pragma once
#include "Scene.h"
#define SPACESHOOT_WINDOW_WIDTH_PX 600                      /* 游戏窗口宽度*/
#define SPACESHOOT_WINDOW_HEIGHT_PX 800                     /* 游戏窗口高度*/
#define SPACESHOOT_WINDOW_TITLE_NAME "spaceshoot"           /* 游戏窗口名称*/
#define SPACESHOOT_IMAGE_FLAG (IMG_INIT_JPG | IMG_INIT_PNG) /* 游戏支持的图片格式*/
/**
 * @brief: 游戏的主类，管理游戏循环和场景切换，配置成单例模式
 * @note: 懒汉式单例模式，在第一次调用getInstance的时候创建唯一的静态对象
 */
class GameManager
{
private:
    bool running_flag = false;                            /* 游戏运行标志*/
    Scene *current_scene = nullptr;                       /* 当前活动场景*/
    int width = SPACESHOOT_WINDOW_WIDTH_PX;               /* 窗口宽度*/
    int height = SPACESHOOT_WINDOW_HEIGHT_PX;             /* 窗口高度*/
    SDL_Window *window = nullptr;                         /* 窗口*/
    SDL_Renderer *renderer = nullptr;                     /* 渲染器*/
    GameManager();                                        /* 构造函数私有*/
    ~GameManager();                                       /* 析构函数私有*/
    GameManager(const GameManager &) = delete;            /* 禁止拷贝构造*/
    GameManager &operator=(const GameManager &) = delete; /* 禁止拷贝赋值*/
public:
    /* 单例接口*/
    static GameManager &getInstance()
    {
        static GameManager instance;
        return instance;
    }
    void init();                         /* 初始化游戏*/
    void run();                          /* 运行游戏资源*/
    void clean();                        /* 清理游戏资源*/
    void change_scene(Scene *scene);     /* 切换游戏场景*/
    void update();                       /* 更新游戏资源*/
    void render();                       /* 渲染*/
    void handle_event(SDL_Event *event); /* 事件处理*/
    /* 访问器/修改器*/
    bool &get_runningFlag() { return running_flag; }
    Scene *&get_currentScene() { return current_scene; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    SDL_Window *&get_window() { return window; }
    SDL_Renderer *&get_renderer() { return renderer; }
};
