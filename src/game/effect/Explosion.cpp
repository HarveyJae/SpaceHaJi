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
    /* 加载texture*/
    SDL_Texture *texture = IMG_LoadTexture(get_game().get_renderer(), SPACESHOOT_EFFECT_EXPLOSION_IMAGE_PATH);
    get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &get_width(), &get_height());
    /* 定义explosion起始坐标*/
    get_point().x = 0;
    get_point().y = 0;
}
void Explosion::update()
{
}
void Explosion::render()
{
    SDL_Rect Explosion_rect{static_cast<int>(get_point().x), static_cast<int>(get_point().y), get_width(), get_height()};
    SDL_RenderCopy(get_game().get_renderer(), get_texture(), nullptr, &Explosion_rect);
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