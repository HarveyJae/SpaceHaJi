#ifndef __SCENE_H__
#define __SCENE_H__
#include <SDL.h>
/**
 * @brief: 定义场景基类s
 */
class Scene
{
private:
    /* data */
public:
    Scene();
    virtual ~Scene() = default;

    virtual void init() = 0;                        /* 初始化场景*/
    virtual void update() = 0;                      /* 更新场景*/
    virtual void render() = 0;                      /* 渲染场景(是否能合并到update函数里面)*/
    virtual void clean() = 0;                       /* 清理场景资源*/
    virtual void handle_event(SDL_Event *event) = 0; /* 处理输入事件*/
};

#endif