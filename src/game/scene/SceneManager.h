#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include "Scene.h"
class SceneManager
{
private:
    /* data */
public:
    SceneManager(/* args */);
    ~SceneManager();

    void change_scene(Scene *scene);
};



#endif