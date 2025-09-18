#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
#include <memory>
#include <vector>

class MainScene : public Scene
{
private:
    Fighter fighter;
    /* bullet数组(bullet里面有引用成员，因此不可拷贝，使用智能指针)*/
    std::vector<std::unique_ptr<Bullet>> bullets; 
    /* 场景键盘控制*/
    void keyboard_ctrl();
public:
    MainScene();
    ~MainScene();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
