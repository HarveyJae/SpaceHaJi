#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdint.h>
#include <random>
#define SPACESHOOT_DEFAULT_FPS 60                           /* 游戏默认帧率*/
#define SPACESHOOT_WINDOW_WIDTH_PX 600                      /* 游戏窗口宽度*/
#define SPACESHOOT_WINDOW_HEIGHT_PX 800                     /* 游戏窗口高度*/
#define SPACESHOOT_WINDOW_TITLE_NAME "spaceshoot"           /* 游戏窗口名称*/
#define SPACESHOOT_IMAGE_FLAG (IMG_INIT_JPG | IMG_INIT_PNG) /* 游戏支持的图片格式*/
#define SPACESHOOT_MIXER_FLAG (MIX_INIT_MP3 | MIX_INIT_OGG) /* 游戏支持的音频格式*/
#define SPACESHOOT_MIXER_FREQUENCE MIX_DEFAULT_FREQUENCY    /* 游戏的音频默认频率*/
#define SPACESHOOT_MIXER_FORMAT MIX_DEFAULT_FORMAT          /* 游戏的音频默认格式*/
#define SPACESHOOT_MIXER_CHANNELS 32                        /* 游戏的音频默认通道数*/
#define SPACESHOOT_MIXER_MAX_VOLUME MIX_MAX_VOLUME          /* 游戏的音频默认最大音量*/
/* 前向声明*/
class Scene;
/**
 * @brief: 游戏的主类，管理游戏循环和场景切换，配置成单例模式
 * @note: 懒汉式单例模式，在第一次调用getInstance的时候创建唯一的静态对象
 * @note: frame_time和fps互为倒数，fps是速度，frame_time是周期
 * @note: frame_time用来控制游戏的绘制速度，即按照既定的帧率绘制游戏画面
 * @note: 速度参数用来控制物体的移动速度只与帧率相关，和当前的物理机器无关
 * @note: speed_arg和frame_time表示含义相同，只不过单位是(s/帧)，如果物体的移动速度是a px/s，那么这个物体一帧应该移动a * speed_arg px
 *
 */
class GameManager
{
private:
    int fps = SPACESHOOT_DEFAULT_FPS;                     /* 游戏帧率(帧/s)*/
    uint32_t frame_time = 0;                              /* 帧时间(ms/帧)*/
    float speed_arg = 0.0;                                /* 速度参数*/
    bool running_flag = false;                            /* 游戏运行标志*/
    Scene *current_scene = nullptr;                       /* 当前活动场景*/
    int width = SPACESHOOT_WINDOW_WIDTH_PX;               /* 窗口宽度*/
    int height = SPACESHOOT_WINDOW_HEIGHT_PX;             /* 窗口高度*/
    SDL_Window *window = nullptr;                         /* 窗口*/
    SDL_Renderer *renderer = nullptr;                     /* 渲染器*/
    std::mt19937 gen;                                     /* 随机数生成器*/
    std::uniform_real_distribution<float> dis;            /* 随机数分布器*/
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

    /* 定义访问器*/
    int &get_fps() { return fps; }
    uint32_t &get_frameTime() { return frame_time; }
    float &get_speedArg() { return speed_arg; }
    bool &get_runningFlag() { return running_flag; }
    Scene *&get_currentScene() { return current_scene; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    SDL_Window *&get_window() { return window; }
    SDL_Renderer *&get_renderer() { return renderer; }
    /* 全局辅助函数*/
    float random() { return dis(gen); }
};
