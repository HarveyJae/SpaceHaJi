#include "MainScene.h"
#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"
MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}
void MainScene::init()
{
    /* 初始化fighter对象*/
    fighter.init();
}
void MainScene::render()
{
    /* 绘制fighter帧*/
    fighter.render();
}
void MainScene::clean()
{
    /* 清除fighter对象*/
    fighter.clean();
}
void MainScene::handle_event(SDL_Event *event)
{
    /* 处理fighter事件*/
    fighter.handle_event(event);
}
void MainScene::update()
{
    /* 更新fighter帧*/
    fighter.update();
}