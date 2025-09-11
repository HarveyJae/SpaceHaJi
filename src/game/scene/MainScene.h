#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__
#include "Scene.h"
class MainScene : public Scene
{
private:
    /* data */
public:
    MainScene(/* args */);
    ~MainScene();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};

#endif