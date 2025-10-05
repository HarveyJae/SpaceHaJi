#include "HappyHaji.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
#define SPACESHOOT_EFFECT_HAPPYHAJI_IMAGE_PATH "../assets/effect/happy_haji.png" /* happy_haji图片路径*/
#define SPACESHOOT_HAPPYHAJI_DEFAULT_FPS 5                                      /* happy_haji的帧率，5fps*/
#define SPACESHOOT_HAPPYHAJI_DEFAULT_TOTAL_FRAME 3                               /* happy_haji的帧数，3 frame*/
HappyHaji::HappyHaji()
{
}

HappyHaji::~HappyHaji()
{
}
void HappyHaji::init()
{
    /* 设置帧率*/
    get_fps() = SPACESHOOT_HAPPYHAJI_DEFAULT_FPS;
    /* 设置帧时间*/
    get_frameTime() = 1000 / get_fps();
    /* 设置帧数*/
    get_totalFrame() = SPACESHOOT_HAPPYHAJI_DEFAULT_TOTAL_FRAME;
    get_curFrame() = 0;
    /* 加载texture*/
    get_texture() = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_EFFECT_HAPPYHAJI_IMAGE_PATH);
    SDL_QueryTexture(get_texture(), nullptr, nullptr, &get_width(), &get_height());
    /* 设置精灵图帧尺寸*/
    get_width() = get_width() / get_totalFrame();
    get_height();
    /* 设置默认效果尺寸，可以在场景中被修改*/
    get_eWidth() = get_width();
    get_eHeight() = get_height();
    /* 定义explosion起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
    /* 初始化时间*/
    get_startTime() = SDL_GetTicks();
}
void HappyHaji::update()
{
    /* 按照效果帧率更新帧数*/
    uint32_t now_time = SDL_GetTicks();
    if (now_time - get_startTime() >= get_frameTime())
    {
        get_curFrame() = (get_curFrame() + 1) % get_totalFrame();
        get_startTime() = now_time;
    }
}
void HappyHaji::render()
{
    /* 源绘制区域*/
    SDL_Rect src_rect = {get_curFrame() * get_eWidth(), 0, get_width(), get_height()};
    /* 目标绘制区域*/
    SDL_Rect dest_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_eWidth(), get_eHeight()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), &src_rect, &dest_rect);
}
void HappyHaji::clean()
{
    if (get_texture())
    {
        SDL_DestroyTexture(get_texture());
    }
}
void HappyHaji::handle_event(SDL_Event *event)
{
}