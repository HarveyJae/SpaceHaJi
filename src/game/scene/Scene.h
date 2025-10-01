#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <map>
/* 前向声明*/
class GameManager;
/**
 * @brief: 定义场景基类
 */
class Scene
{
private:
    GameManager &game;
    /* 图片纹理*/
    SDL_Texture *texture = nullptr;
    /* 音频对象*/
    Mix_Music *music = nullptr;
    /* 音效列表*/
    std::map<std::string, Mix_Chunk *> sounds;

public:
    Scene();
    virtual ~Scene() = default;

    virtual void init() = 0;                         /* 初始化场景*/
    virtual void update() = 0;                       /* 更新场景*/
    virtual void render() = 0;                       /* 渲染场景(是否能合并到update函数里面)*/
    virtual void clean() = 0;                        /* 清理场景资源*/
    virtual void handle_event(SDL_Event *event) = 0; /* 处理输入事件*/
    /* 定义修改器/访问器*/
    SDL_Texture *&get_texture() { return texture; }
    Mix_Music *&get_music() { return music; }
    std::map<std::string, Mix_Chunk *> &get_sounds() { return sounds; }
    GameManager &get_game() { return game; }
};
