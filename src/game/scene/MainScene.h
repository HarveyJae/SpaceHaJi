#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
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
    /* 随机数生成器*/
    std::mt19937 gen;
    /* 随机数分布器*/
    std::uniform_real_distribution<float> dis;
    /* 场景键盘控制*/
    void keyboard_ctrl();
    /* enemy生成器*/
    void create_enemy();
    /* 更新fighter*/
    void update_fighter();
    /* 更新enemy*/
    void update_enemy();
    /* 更新bullet*/
    void update_fighterBullet();
    void update_enemyBullet();
    /* 绘制fighter*/
    void render_fighter();
    /* 绘制enemy*/
    void render_enemy();
    /* 绘制bullet*/
    void render_fighterBullet();
    void render_enemyBullet();
    /* 清除fighter*/
    void clean_fighter();
    /* 清理enemy*/
    void clean_enemy();
    /* 清理bullet*/
    void clean_fighterBullet();
    void clean_enemyBullet();
    /* 爆炸*/
    void explode_fighter(Fighter *fighter);
    void explode_enemy(Enemy *enemy);

public:
    MainScene();
    ~MainScene();

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
