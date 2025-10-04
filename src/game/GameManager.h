#pragma once
#include "SDL.h"
#include <string>
#include <cstdint>
#include <random>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
/* 前向声明*/
class Scene;
class TTF_Font;
class HudManager;
/**
 * @brief: 游戏的主类，管理游戏循环和场景切换，配置成单例模式
 * @note:  懒汉式单例模式，在第一次调用getInstance的时候创建唯一的静态对象
 * @note:  frame_time和fps互为倒数，fps是速度，frame_time是周期
 * @note:  frame_time用来控制游戏的绘制速度，即按照既定的帧率绘制游戏画面
 * @note:  速度参数用来控制物体的移动速度只与帧率相关，和当前的物理机器无关
 * @note:  speed_arg和frame_time表示含义相同，只不过单位是(s/帧)，如果物体的移动速度是a px/s，那么这个物体一帧应该移动a * speed_arg px
 *
 */
class GameManager
{
public:
    enum class NormalFontType
    {
        None = 0,
        Small,
        Medium,
        Large,
        NormalFontTypeMax,
    };

private:
    /* 私有成员*/
    int fps = 0;                               /* 游戏帧率(帧/s)*/
    uint32_t frame_time = 0;                   /* 帧时间(ms/帧)*/
    float speed_arg = 0.0;                     /* 速度参数*/
    bool running_flag = false;                 /* 游戏运行标志*/
    std::unique_ptr<Scene> current_scene;      /* 当前活动场景*/
    int width = 0;                             /* 窗口宽度*/
    int height = 0;                            /* 窗口高度*/
    SDL_Window *window = nullptr;              /* 窗口*/
    SDL_Renderer *renderer = nullptr;          /* 渲染器*/
    TTF_Font *text_font_small = nullptr;       /* 通用文本字体(小)*/
    TTF_Font *text_font_medium = nullptr;      /* 通用文本字体(中)*/
    TTF_Font *text_font_large = nullptr;       /* 通用文本字体(大)*/
    std::mt19937 gen;                          /* 随机数生成器*/
    std::uniform_real_distribution<float> dis; /* 随机数分布器*/
    std::unique_ptr<HudManager> hud = nullptr; /* hud管理器*/
    uint32_t SDL_ChangeScene_Event = 0;        /* SDL自定义场景切换事件*/
    std::thread cs_timer_thread;               /* 场景切换延时线程*/
    std::mutex cs_mutex;                       /* 场景切换锁*/
    std::condition_variable cs_cv;             /* 场景切换条件变量*/
    bool cs_stop_flag = false;                 /* 场景切换取消标志*/
    std::atomic<bool> cs_timer_active{false};  /* 场景切换延时任务活跃标志*/
    std::unique_ptr<Scene> pending_scene;      /* 待切换场景*/
    /* 私有方法*/
    void start_cs_timer_thread(uint32_t delay_ms);        /* 启动场景延时切换线程*/
    void cs_timer_thread_function(uint32_t delay_ms);     /* 场景延时线程函数*/
    void change_sceneStop();                              /* 停止场景切换*/
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
    void init();                                                             /* 初始化游戏*/
    void run();                                                              /* 运行游戏资源*/
    void clean();                                                            /* 清理游戏资源*/
    void update();                                                           /* 更新游戏资源*/
    void render();                                                           /* 渲染*/
    void handle_event(SDL_Event *event);                                     /* 事件处理*/
    void change_sceneNow(std::unique_ptr<Scene> scene);                      /* 切换游戏场景*/
    void change_sceneDelay(std::unique_ptr<Scene> scene, uint32_t delay_ms); /* 延时切换游戏场景*/

    /* 定义访问器*/
    int &get_fps() { return fps; }
    uint32_t &get_frameTime() { return frame_time; }
    float &get_speedArg() { return speed_arg; }
    bool &get_runningFlag() { return running_flag; }
    Scene &get_currentScene() { return *current_scene; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    SDL_Window *&get_window() { return window; }
    SDL_Renderer *&get_renderer() { return renderer; }
    HudManager &get_hud() { return *hud; }
    /* 全局辅助函数*/
    float random() { return dis(gen); }
    void RenderTextCenterW(std::string &text, NormalFontType type, SDL_Color &color, float height_percent);
};
