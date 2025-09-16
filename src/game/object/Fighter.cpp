#include "Fighter.h"
#include "GameManager.h"
#include "SDL.h"
#include "SDL_image.h"
Fighter::Fighter()
{
}
Fighter::~Fighter()
{
}
void Fighter::init()
{
    /* 配置fighter默认移动速度*/
    get_speed() = SPACESHOOT_FIGHTER_DEFAULT_SPEED;
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 等比例缩放fighter图片*/
    get_width() = get_width() / 2;
    get_height() = get_height() / 2;
    /* 定义fighter起始坐标*/
    get_point().x = get_game().get_width() / 2 - get_width() / 2;
    get_point().y = get_game().get_height() - get_height();
}
void Fighter::update()
{
    keyboard_ctrl();
}
void Fighter::render()
{
    SDL_Rect Fighter_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Fighter_rect);
}
void Fighter::clean()
{
    if (get_texture() != nullptr)
    {
        SDL_DestroyTexture(get_texture());
    }
}
void Fighter::handle_event(SDL_Event *event)
{
}
void Fighter::keyboard_ctrl()
{
    /* 状态查询获取当前的键盘状态*/
    const uint8_t *keyboard_state = SDL_GetKeyboardState(nullptr);
    if (keyboard_state[SDL_SCANCODE_W])
    {
        /* 控制fighter*/
        get_point().y -= get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (get_point().y <= 0)
        {
            get_point().y = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_A])
    {
        /* 控制fighter*/
        get_point().x -= get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (get_point().x <= 0)
        {
            get_point().x = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        /* 控制fighter*/
        get_point().y += get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (get_point().y >= (get_game().get_height() - get_height()))
        {
            get_point().y = (get_game().get_height() - get_height());
        }
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        /* 控制fighter*/
        get_point().x += get_speed() * get_game().get_speedArg();
        /* 限制fighter移动范围*/
        if (get_point().x >= (get_game().get_width() - get_width()))
        {
            get_point().x = (get_game().get_width() - get_width());
        }
    }
}