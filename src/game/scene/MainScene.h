#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include <memory>
#include <vector>
#include <random>

/* 前置声明*/
class GameObject;
class MainScene : public Scene
{
private:
    Fighter fighter;
    /* enemy数组*/
    std::vector<std::unique_ptr<Enemy>> enemys;
    /* bullet数组*/
    std::vector<std::unique_ptr<Bullet>> bullets;
    /* explosion数组*/
    std::vector<std::unique_ptr<Explosion>> explosions;
    /* 随机数生成器*/
    std::mt19937 gen;
    /* 随机数分布器*/
    std::uniform_real_distribution<float> dis;
    /* 场景键盘控制*/
    void keyboard_ctrl();
    /* enemy生成器*/
    void create_enemy();
    /* 更新*/
    void update_fighter();
    void update_enemy();
    void update_bullet();
    void update_explosion();
    /* 绘制*/
    void render_fighter();
    void render_enemy();
    void render_bullet();
    void render_explosion();
    /* 清除*/
    void clean_fighter();
    void clean_enemy();
    void clean_bullet();
    void clean_explosion();
    /* 辅助函数*/
    bool bullet_collisionDetection(Bullet *bullet, GameObject *obj);
public:
    MainScene();
    ~MainScene() override;

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
