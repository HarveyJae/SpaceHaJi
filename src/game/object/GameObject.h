#pragma once
#include <SDL.h>
#include <stdint.h>
class GameObject
{
private:
    /* 图片纹理*/
    SDL_Texture *texture = nullptr;
    /* 像素位置*/
    SDL_FPoint pos{0, 0};
    /* 颜色(默认为纯白)*/
    SDL_Color color{255, 255, 255, 255};
    /* 尺寸*/
    int width = 0;
    int height = 0;
    /* 生命标志位*/
    bool active = false; /* 活动标志*/
    bool dead = false;   /* 删除标志*/
public:
    GameObject() {};
    virtual ~GameObject() = default;
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handle_event(SDL_Event *event) = 0;
    /* 定义访问器/修改器*/
    SDL_Texture *&get_texture() { return texture; }
    SDL_FPoint &get_point() { return pos; }
    SDL_Color &get_color() { return color; }
    int &get_width() { return width; }
    int &get_height() { return height; }
    bool &get_active() { return active; }
    bool &get_dead() { return dead; }
    /* 定义修改器*/
    void set_texture(SDL_Texture *texture) { this->texture = texture; }
    void set_point(SDL_FPoint pos) { this->pos = pos; }
    void set_point(float x, float y)
    {
        this->pos.x = x;
        this->pos.y = y;
    }
    void set_color(SDL_Color color) { this->color = color; }
    void set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
    }
    void set_width(int width) { this->width = width; }
    void set_height(int height) { this->height = height; }
    void set_active(bool active) { this->active = active; }
    void set_dead(bool dead) { this->dead = dead; }
};
