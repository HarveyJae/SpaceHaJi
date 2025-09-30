#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include <memory>
#include <vector>
#include <random>

class MainScene : public Scene
{
private:
    Fighter fighter;
    /* fighter_bullet数组(bullet里面有引用成员，因此不可拷贝，使用智能指针)*/
    std::vector<std::unique_ptr<Bullet>> fighter_bullets;
    /* enemy数组*/
    std::vector<std::unique_ptr<Enemy>> enemys;
    /* enemy_bullet数组*/
    std::vector<std::unique_ptr<Bullet>> enemy_bullets;
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
    void update_fighterBullet();
    void update_enemyBullet();
    void update_explosion();
    /* 绘制*/
    void render_fighter();
    void render_enemy();
    void render_fighterBullet();
    void render_enemyBullet();
    void render_explosion();
    /* 清除*/
    void clean_fighter();
    void clean_enemy();
    void clean_fighterBullet();
    void clean_enemyBullet();
    void clean_explosion();

public:
    MainScene();
    ~MainScene() override;

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
