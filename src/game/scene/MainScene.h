#pragma once
#include "Scene.h"
#include "Fighter.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Item.h"
#include <memory>
#include <vector>

#define SPACESHOOT_MAINSCENE_MUSIC_PATH "../assets/music/manbobo.mp3"          /* mainscene的背景音乐路径*/
#define SPACESHOOT_FIGHTER_SHOOT_SOUND_PATH "../assets/sound/laser_shoot4.wav" /* fighter-shoot的音效路径*/
#define SPACESHOOT_ENEMY_SHOOT_SOUND_PATH "../assets/sound/xs_laser.wav"       /* enemy-shoot的音效路径*/
#define SPACESHOOT_FIGHTER_EXPLODE_SOUND_PATH "../assets/sound/explosion1.wav" /* fighter-explode的音效路径*/
#define SPACESHOOT_ENEMY_EXPLODE_SOUND_PATH "../assets/sound/ohyeah.mp3"       /* enemy-explode的音效路径*/
#define SPACESHOOT_HIT_SOUND_PATH "../assets/sound/eff11.wav"                  /* bullet-hit的音效路径*/
#define SPACESHOOT_FIGHTER_BONUS_SOUND_PATH "../assets/sound/eff5.mp3"         /* fighter-bonus的音效路径*/
#define SPACESHOOT_FIGHTER_SHOOT_SOUND_KEY "fighter_shoot"                     /* fighter-shoot的key值*/
#define SPACESHOOT_ENEMY_SHOOT_SOUND_KEY "enemy_shoot"                         /* enemy-shoot的key值*/
#define SPACESHOOT_FIGHTER_EXPLODE_SOUND_KEY "fighter_explode"                 /* fighter-explode的key值*/
#define SPACESHOOT_ENEMY_EXPLODE_SOUND_KEY "enemy_explode"                     /* enemy-explode的key值*/
#define SPACESHOOT_HIT_SOUND_SOUND_KEY "bullet_hit"                            /* bullet-hit的key值*/
#define SPACESHOOT_FIGHTER_BONUS_SOUND_KEY "fighter_bonus"                     /* fighter-bonus的key值*/
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
    /* item数组*/
    std::vector<std::unique_ptr<Item>> items;
    /* explosion数组*/
    std::vector<std::unique_ptr<Explosion>> explosions;
    /* 场景键盘控制*/
    void keyboard_ctrl();
    /* enemy生成器*/
    void create_enemy();
    /* 更新*/
    void update_fighter();
    void update_enemy();
    void update_bullet();
    void update_item();
    void update_explosion();
    /* 绘制*/
    void render_fighter();
    void render_enemy();
    void render_bullet();
    void render_item();
    void render_explosion();
    /* 清除*/
    void clean_fighter();
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
