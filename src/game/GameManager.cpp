#include "GameManager.h"
#include <iostream>
#include "Scene.h"
#include "TitleScene.h"
#include "HudManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdint.h>
#include <chrono>
#define SPACESHOOT_DEFAULT_FPS 60                                                /* 游戏默认帧率*/
#define SPACESHOOT_WINDOW_WIDTH_PX 600                                           /* 游戏窗口宽度*/
#define SPACESHOOT_WINDOW_HEIGHT_PX 800                                          /* 游戏窗口高度*/
#define SPACESHOOT_WINDOW_TITLE_NAME "SpaceHaJi"                                 /* 游戏窗口名称*/
#define SPACESHOOT_IMAGE_FLAG (IMG_INIT_JPG | IMG_INIT_PNG)                      /* 游戏支持的图片格式*/
#define SPACESHOOT_MIXER_FLAG (MIX_INIT_MP3 | MIX_INIT_OGG)                      /* 游戏支持的音频格式*/
#define SPACESHOOT_MIXER_FREQUENCE MIX_DEFAULT_FREQUENCY                         /* 游戏的音频默认频率*/
#define SPACESHOOT_MIXER_FORMAT MIX_DEFAULT_FORMAT                               /* 游戏的音频默认格式*/
#define SPACESHOOT_MIXER_CHANNELS 32                                             /* 游戏的音频默认通道数*/
#define SPACESHOOT_MIXER_MAX_VOLUME MIX_MAX_VOLUME                               /* 游戏的音频默认最大音量*/
#define SPACESHOOT_NORMAL_TEXT_FONT_PATH "../assets/font/VonwaonBitmap-16px.ttf" /* text字体路径*/
#define SPACESHOOT_NORMAL_TEXT_FONT_SMALL_SIZE 32                                /* text字体大小(小)*/
#define SPACESHOOT_NORMAL_TEXT_FONT_MEDIUM_SIZE 48                               /* text字体大小(中)*/
#define SPACESHOOT_NORMAL_TEXT_FONT_LARGE_SIZE 64                                /* text字体大小(大)*/
GameManager::GameManager() : fps(SPACESHOOT_DEFAULT_FPS), width(SPACESHOOT_WINDOW_WIDTH_PX), height(SPACESHOOT_WINDOW_HEIGHT_PX)
{
    /* 获取随机数种子*/
    std::random_device rd;
    /* 初始化随机数分配器*/
    gen = std::mt19937(rd());
    /* 初始化随机数分布器*/
    dis = std::uniform_real_distribution<float>(0.0f, 1.0f);
    /* 配置帧时间*/
    get_frameTime() = 1000 / get_fps();
    /* 配置速度参数*/
    get_speedArg() = 1.0 / get_fps();
}

GameManager::~GameManager()
{
    change_sceneStop();
    clean();
}

void GameManager::init()
{
    /* SDL初始化*/
    int retval = 0;
    retval = SDL_Init(SDL_INIT_EVERYTHING);
    if (retval != 0)
    {
        std::cerr << "SDL Init failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 创建窗口*/
    window = SDL_CreateWindow(SPACESHOOT_WINDOW_TITLE_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL Create window failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 创建渲染器*/
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "SDL Create renderer failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 设定逻辑渲染尺寸，窗口缩放时自动按基础分辨率拉伸 */
    retval = SDL_RenderSetLogicalSize(renderer, width, height);
    if (retval != 0)
    {
        std::cerr << "SDL logical size set failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 配置渲染器的默认颜色*/
    retval = SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    if (retval != 0)
    {
        std::cerr << "SDL default color set failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 初始化SDL_image*/
    retval = IMG_Init(SPACESHOOT_IMAGE_FLAG);
    if (retval != SPACESHOOT_IMAGE_FLAG)
    {
        std::cerr << "SDL_image init failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 初始化SDL_mixer*/
    retval = Mix_Init(SPACESHOOT_MIXER_FLAG);
    if (retval != SPACESHOOT_MIXER_FLAG)
    {
        std::cerr << "SDL_mixer init failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 初始化SDL_ttf*/
    retval = TTF_Init();
    if (retval != 0)
    {
        std::cerr << "SDL_ttf init failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 音频开启*/
    retval = Mix_OpenAudio(SPACESHOOT_MIXER_FREQUENCE, SPACESHOOT_MIXER_FORMAT, 2, SPACESHOOT_MIXER_MAX_VOLUME);
    if (retval < 0)
    {
        std::cerr << "SDL_mixer open failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 设置音效通道数量*/
    Mix_AllocateChannels(SPACESHOOT_MIXER_CHANNELS);
    /* 设置音乐音量*/
    Mix_VolumeMusic(SPACESHOOT_MIXER_MAX_VOLUME / 4);
    Mix_Volume(-1, SPACESHOOT_MIXER_MAX_VOLUME / 8);
    /* 加载通用字体*/
    text_font_small = TTF_OpenFont(SPACESHOOT_NORMAL_TEXT_FONT_PATH, SPACESHOOT_NORMAL_TEXT_FONT_SMALL_SIZE);
    if (!text_font_small)
    {
        std::cerr << "Load small text font failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    text_font_medium = TTF_OpenFont(SPACESHOOT_NORMAL_TEXT_FONT_PATH, SPACESHOOT_NORMAL_TEXT_FONT_MEDIUM_SIZE);
    if (!text_font_medium)
    {
        std::cerr << "Load medium text font failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    text_font_large = TTF_OpenFont(SPACESHOOT_NORMAL_TEXT_FONT_PATH, SPACESHOOT_NORMAL_TEXT_FONT_LARGE_SIZE);
    if (!text_font_large)
    {
        std::cerr << "Load large text font failed, error msg: " << SDL_GetError() << std::endl;
        running_flag = false;
        return;
    }
    /* 注册场景切换事件*/
    SDL_ChangeScene_Event = SDL_RegisterEvents(1);
    if (SDL_ChangeScene_Event == (uint32_t)-1)
    {
        std::cerr << "SDL_Event ChangeScene register failed." << std::endl;
        running_flag = false;
        return;
    }
    /* 初始化hud管理器*/
    hud = std::make_unique<HudManager>();
    hud->init();
    /* 创建主场景*/
    change_sceneNow(std::make_unique<TitleScene>());
    running_flag = true;
}
void GameManager::run()
{
    uint32_t now_time = SDL_GetTicks();
    uint32_t last_time = now_time;
    while (running_flag)
    {
        /* 执行1帧*/
        if (now_time - last_time >= frame_time)
        {
            if (current_scene == nullptr)
            {
                std::cerr << "Current scene is null, quit game." << std::endl;
                return;
            }
            SDL_Event event;
            handle_event(&event); /* 处理场景事件*/
            update();             /* 更新*/
            render();             /* 绘制*/
            last_time = now_time;
        }
        now_time = SDL_GetTicks();
    }
}
void GameManager::clean()
{
    if (current_scene)
    {
        current_scene->clean();
        current_scene.reset();
    }
    if (hud)
    {
        hud->clean();
        hud.reset();
    }
    if (text_font_small)
    {
        TTF_CloseFont(text_font_small);
        text_font_small = nullptr;
    }
    if (text_font_medium)
    {
        TTF_CloseFont(text_font_medium);
        text_font_medium = nullptr;
    }
    if (text_font_large)
    {
        TTF_CloseFont(text_font_large);
        text_font_large = nullptr;
    }
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    /* 避免重复释放*/
    renderer = nullptr;
    SDL_DestroyWindow(window);
    /* 避免重复释放*/
    window = nullptr;
    SDL_Quit();
}
void GameManager::change_sceneNow(std::unique_ptr<Scene> scene)
{
    if (!scene)
    {
        return;
    }
    if (current_scene)
    {
        current_scene->clean();
    }
    current_scene = std::move(scene);
    current_scene->init();
}
void GameManager::change_sceneDelay(std::unique_ptr<Scene> scene, uint32_t delay_ms)
{
    /* 取消尚未完成的场景切换任务并回收线程资源*/
    change_sceneStop();
    /* 挂起待切换场景*/
    cs_mutex.lock();
    pending_scene = std::move(scene);
    cs_mutex.unlock();

    /* 延时为0,直接投递场景切换事件*/
    if (delay_ms == 0)
    {
        SDL_Event event;
        event.type = SDL_ChangeScene_Event;
        if (SDL_PushEvent(&event) != 1)
        {
            std::cerr << "Scene change event push error." << std::endl;
        }
        return;
    }
    /* 启动延时线程*/
    start_cs_timer_thread(delay_ms);
}
void GameManager::start_cs_timer_thread(uint32_t delay_ms)
{
    cs_timer_active = true;
    cs_timer_thread = std::thread(&GameManager::cs_timer_thread_function, this, delay_ms);
}
void GameManager::cs_timer_thread_function(uint32_t delay_ms)
{
    const std::chrono::steady_clock::time_point dead_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(delay_ms);
    std::unique_lock<std::mutex> cv_lock(cs_mutex);
    bool t_cancel_flag = cs_cv.wait_until(cv_lock, dead_time, [this]
                                          { return cs_stop_flag; });
    cv_lock.unlock();

    /* 检测是否已被外部取消或析构*/
    if (!cs_timer_active.load())
    {
        return;
    }
    /* 检测是否提前唤醒*/
    if (t_cancel_flag)
    {
        return;
    }
    /* 时间到，发送场景切换事件*/
    SDL_Event event;
    event.type = SDL_ChangeScene_Event;
    if (SDL_PushEvent(&event) < 0)
    {
        std::cerr << "SDL_Event ChangeScene register failed." << std::endl;
    }
}
void GameManager::change_sceneStop()
{
    /* 设置取消标记并判断是否存在活跃计时器，存在则唤醒计时线程*/
    if (cs_timer_active.exchange(false))
    {
        /* 设置取消场景切换标志*/
        cs_mutex.lock();
        cs_stop_flag = true;
        cs_mutex.unlock();

        /* 唤醒计时线程的wait_until*/
        cs_cv.notify_all();

        /* 等待计时线程退出*/
        if (cs_timer_thread.joinable())
        {
            cs_timer_thread.join();
        }
        /* 清理等待切换的挂起场景*/
        cs_mutex.lock();
        pending_scene.reset();
        cs_mutex.unlock();

        /* 恢复取消场景切换标志*/
        cs_mutex.lock();
        cs_stop_flag = false;
        cs_mutex.unlock();
    }
}
void GameManager::update()
{
    /* 更新场景事件*/
    if (current_scene != nullptr)
    {
        current_scene->update();
    }
}
void GameManager::render()
{
    /* 清空渲染器*/
    SDL_RenderClear(renderer);
    /* 绘制场景事件*/
    if (current_scene != nullptr)
    {
        current_scene->render();
    }
    /* 显示更新*/
    SDL_RenderPresent(renderer);
}
void GameManager::handle_event(SDL_Event *event)
{
    /* 事件分发*/
    while (SDL_PollEvent(event))
    {
        /* 处理退出事件*/
        if (event->type == SDL_QUIT)
        {
            running_flag = false;
        }
        /* 场景切换事件*/
        if (event->type == SDL_ChangeScene_Event)
        {
            /* 清理线程资源*/
            if (cs_timer_active.exchange(false))
            {
                if (cs_timer_thread.joinable())
                {
                    cs_timer_thread.join();
                }
            }
            /* 切换挂起场景*/
            std::unique_ptr<Scene> next_scene;
            cs_mutex.lock();
            if (pending_scene)
            {
                next_scene = std::move(pending_scene);
            }
            cs_mutex.unlock();
            if (next_scene)
            {
                change_sceneNow(std::move(next_scene));
            }
        }
        /* 处理按键事件*/
        if (event->type == SDL_KEYDOWN)
        {
            /* 修饰键alt*/
            const bool hold_alt = (event->key.keysym.mod & KMOD_ALT) != 0;
            /* alt + Enter*/
            if (hold_alt && event->key.keysym.sym == SDLK_RETURN)
            {
                fullScreen_flag = !fullScreen_flag;
                SDL_SetWindowFullscreen(window, fullScreen_flag ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
            }
        }
        /* 处理场景事件*/
        if (current_scene != nullptr)
        {
            current_scene->handle_event(event);
        }
    }
}
/**
 * @brief: 在窗口宽度中心绘制文本
 * @param: text: 绘制文字
 * @param: type: 字体类型
 * @param: color: 文字颜色
 * @param: height_percent: 绘制文字所在的高度(百分比)
 * @return: 文本末尾坐标
 */
SDL_Point GameManager::RenderTextCenterW(std::string &text, NormalFontType type, SDL_Color &color, float height_percent)
{
    SDL_Point text_Point{0, 0};
    SDL_Surface *text_surface = nullptr;
    /* 类型越界检测*/
    if (type < NormalFontType::None || type >= NormalFontType::NormalFontTypeMax)
    {
        type = NormalFontType::None;
    }
    /* 字体类型选择*/
    switch (type)
    {
    /* 避免编译警告*/
    case NormalFontType::NormalFontTypeMax:
    case NormalFontType::None:
        /* nothing to do*/
        return {0, 0};
    case NormalFontType::Small:
        text_surface = TTF_RenderUTF8_Solid(text_font_small, text.c_str(), color);
        break;
    case NormalFontType::Medium:
        text_surface = TTF_RenderUTF8_Solid(text_font_medium, text.c_str(), color);
        break;
    case NormalFontType::Large:
        text_surface = TTF_RenderUTF8_Solid(text_font_large, text.c_str(), color);
        break;
    }
    if (!text_surface)
    {
        return {0, 0};
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture)
    {
        SDL_FreeSurface(text_surface);
        return {0, 0};
    }
    text_Point.x = width / 2 - text_surface->w / 2;
    text_Point.y = static_cast<int>((height - text_surface->h) * height_percent);
    SDL_Rect text_rect{text_Point.x, text_Point.y, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    /* 返回绘制字体的结束坐标*/
    return {text_rect.x + text_rect.w, text_rect.y};
}
/**
 * @brief: 在窗口的任意坐标绘制文本
 * @param: text: 绘制文字
 * @param: type: 字体类型
 * @param: color: 文本颜色
 * @param: point: 绘制文本的起始坐标
 */
void GameManager::RenderTextPoint(std::string &text, NormalFontType type, SDL_Color &color, SDL_Point &point)
{
    SDL_Surface *text_surface = nullptr;
    /* 类型越界检测*/
    if (type < NormalFontType::None || type >= NormalFontType::NormalFontTypeMax)
    {
        type = NormalFontType::None;
    }
    /* 字体类型选择*/
    switch (type)
    {
    /* 避免编译警告*/
    case NormalFontType::NormalFontTypeMax:
    case NormalFontType::None:
        /* nothing to do*/
        return;
    case NormalFontType::Small:
        text_surface = TTF_RenderUTF8_Solid(text_font_small, text.c_str(), color);
        break;
    case NormalFontType::Medium:
        text_surface = TTF_RenderUTF8_Solid(text_font_medium, text.c_str(), color);
        break;
    case NormalFontType::Large:
        text_surface = TTF_RenderUTF8_Solid(text_font_large, text.c_str(), color);
        break;
    }
    if (!text_surface)
    {
        return;
    }
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture)
    {
        SDL_FreeSurface(text_surface);
        return;
    }
    SDL_Rect text_rect{point.x, point.y, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}
