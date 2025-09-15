#include "MainScene.h"
#include "main.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
MainScene::MainScene() : game(GameManager::getInstance())
{
}

MainScene::~MainScene()
{
}
void MainScene::init()
{
    SDL_Texture *texture = IMG_LoadTexture(game.get_renderer(), SPACESHOOT_OBJECT_FIGHTER_IMAGE_PATH);
    fighter.get_texture() = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &fighter.get_width(), &fighter.get_height());
    fighter.get_point().x = game.get_width() / 2 - fighter.get_width() / 2;
    fighter.get_point().y = game.get_height() - fighter.get_height();
}
void MainScene::render()
{
    SDL_Rect Fighter_rect{static_cast<int>(fighter.get_point().x), static_cast<int>(fighter.get_point().y), fighter.get_width(), fighter.get_height()};
    SDL_RenderCopy(game.get_renderer(), fighter.get_texture(), nullptr, &Fighter_rect);
}
void MainScene::clean()
{
    if (fighter.get_texture() != nullptr)
    {
        SDL_DestroyTexture(fighter.get_texture());
    }
}
void MainScene::handle_event(SDL_Event *event)
{
}
void MainScene::update()
{
    keyboard_ctrl();
}
void MainScene::keyboard_ctrl()
{
    /* 状态查询获取当前的键盘状态*/
    const uint8_t *keyboard_state = SDL_GetKeyboardState(nullptr);
    if (keyboard_state[SDL_SCANCODE_W])
    {
        /* 控制fighter*/
        fighter.get_point().y -= SPACESHOOT_OBJECT_MOVEMENT_SCALE;
        /* 限制fighter移动范围*/
        if (fighter.get_point().y <= 0)
        {
            fighter.get_point().y = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_A])
    {
        /* 控制fighter*/
        fighter.get_point().x -= SPACESHOOT_OBJECT_MOVEMENT_SCALE;
        /* 限制fighter移动范围*/
        if (fighter.get_point().x <= 0)
        {
            fighter.get_point().x = 0;
        }
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        /* 控制fighter*/
        fighter.get_point().y += SPACESHOOT_OBJECT_MOVEMENT_SCALE;
        /* 限制fighter移动范围*/
        if (fighter.get_point().y >= (game.get_height() - fighter.get_height()))
        {
            fighter.get_point().y = (game.get_height() - fighter.get_height());
        }
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        /* 控制fighter*/
        fighter.get_point().x += SPACESHOOT_OBJECT_MOVEMENT_SCALE;
        /* 限制fighter移动范围*/
        if (fighter.get_point().x >= (game.get_width() - fighter.get_width()))
        {
            fighter.get_point().x = (game.get_width() - fighter.get_width());
        }
    }
}