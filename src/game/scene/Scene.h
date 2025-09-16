#pragma once
#include <SDL.h>
/* 前向声明*/
class GameManager;
/**
 * @brief: 定义场景基类
 */
class Scene
{
private:
    GameManager &game;

public:
    Scene();
    virtual ~Scene() = default;

    virtual void init() = 0;                         /* 初始化场景*/
    virtual void update() = 0;                       /* 更新场景*/
    virtual void render() = 0;                       /* 渲染场景(是否能合并到update函数里面)*/
    virtual void clean() = 0;                        /* 清理场景资源*/
    virtual void handle_event(SDL_Event *event) = 0; /* 处理输入事件*/
    /* 定义修改器/访问器*/
    GameManager &get_game() { return game; }
};
