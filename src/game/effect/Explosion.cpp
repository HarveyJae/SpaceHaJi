#include "Explosion.h"
#include "SDL.h"
#include "SDL_image.h"
#include "GameManager.h"
Explosion::Explosion()
{
}
Explosion::~Explosion()
{
}
void Explosion::init()
{
    /* 设置帧率*/
    get_fps() = SPACESHOOT_EXPLOSION_DEFAULT_FPS;
    /* 设置帧时间*/
    get_frameTime() = 1000 / get_fps();
    /* 设置帧数*/
    get_totalFrame() = SPACESHOOT_EXPLOSION_DEFAULT_TOTAL_FRAME;
    get_curFrame() = 0;
    /* 加载texture*/
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_EFFECT_EXPLOSION_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
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
void Explosion::update()
{
    if (get_curFrame() > get_totalFrame())
    {
        /* 效果完成*/
        get_finish() = true;
        return;
    }
    /* 按照效果帧率更新帧数*/
    uint32_t now_time = SDL_GetTicks();
    if (now_time - get_startTime() >= get_frameTime())
    {
        get_curFrame()++;
        get_startTime() = now_time;
    }
}
void Explosion::render()
{
    /* 源绘制区域*/
    SDL_Rect src_rect = {get_curFrame() * get_eWidth(), 0, get_width(), get_height()};
    /* 目标绘制区域*/
    SDL_Rect dest_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_eWidth(), get_eHeight()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), &src_rect, &dest_rect);
}
void Explosion::clean()
{
    if (get_texture() != nullptr)
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Explosion::handle_event(SDL_Event *event)
{
}