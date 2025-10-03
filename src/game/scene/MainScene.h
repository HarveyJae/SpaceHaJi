#pragma once
#include "Scene.h"
#include "HudState.h"
#include <memory>
#include <vector>
/* 前置声明*/
class GameObject;
class Fighter;
class Enemy;
class Bullet;
class Explosion;
class Item;
class MainScene : public Scene
{
private:
    /* fighter对象*/
    std::unique_ptr<Fighter> fighter;
    /* enemy数组*/
    std::vector<std::unique_ptr<Enemy>> enemys;
    /* bullet数组*/
    std::vector<std::unique_ptr<Bullet>> bullets;
    /* item数组*/
    std::vector<std::unique_ptr<Item>> items;
    /* explosion数组*/
    std::vector<std::unique_ptr<Explosion>> explosions;
    /* HudState对象*/
    HudState hud_state;
    /* 场景键盘控制*/
    void keyboard_ctrl();
    /* enemy生成器*/
    void create_enemy();
    /* 更新*/
    void update_fighter();
    void update_bkScroller();
    void update_enemy();
    void update_bullet();
    void update_item();
    void update_explosion();
    void update_hudManager();
    /* 绘制*/
    void render_fighter();
    void render_bkScroller();
    void render_enemy();
    void render_bullet();
    void render_item();
    void render_explosion();
    void render_hudManager();
    /* 清除*/
    void clean_fighter();
    void clean_bkScroller();
    void clean_enemy();
    void clean_bullet();
    void clean_item();
    void clean_explosion();
    /* 辅助函数*/
    bool bullet_collisionDetection(Bullet *bullet, GameObject *obj);
    bool item_collisionDetection(Item *bullet, GameObject *obj);

public:
    MainScene();
    ~MainScene() override;

    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handle_event(SDL_Event *event) override;
};
