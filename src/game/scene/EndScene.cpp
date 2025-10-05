#include "EndScene.h"
#include "GameManager.h"
#include "HudManager.h"
#include "HudState.h"
#include "MainScene.h"
#include <iostream>
#include <fstream>
#define SPACESHOOT_RANK_BOARD_MAX_ITEM 8 /* 排行榜中的最大条目数量*/
#define SPACESHOOT_RANK_BOARD_FILE_PATH "../assets/rank_board.dat"
EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}
void EndScene::init()
{
    /* 设置hud类型*/
    get_game().get_hud().set_sceneType(HudManager::HudSceneType::End);
    /* 读取rank_file*/
    read_rankFile();
    /* 开启文本输入功能*/
    if (!SDL_IsTextInputActive())
    {
        SDL_StartTextInput();
    }
    if (!SDL_IsTextInputActive())
    {
        std::cerr << "EndScene text input open failed, error msg: " << SDL_GetError() << std::endl;
        return;
    }
    /* 初始化定时器*/
    timer = 0;
    /* 开启输入标志*/
    typing_flag = true;
    /* 获取hud_state*/
    hud_state = get_game().get_hud().get_hudState();
}
void EndScene::update()
{
    get_game().get_hud().update(hud_state);
    /* 更新计时器(循环计时1000ms)*/
    timer += get_game().get_frameTime();
    if (timer >= 1000)
    {
        timer = 0;
    }
}
void EndScene::render()
{
    /* 渲染hud*/
    get_game().get_hud().render();
    /* 渲染结束文字*/
    if (typing_flag)
    {
        render_textTyping();
    }
    else
    {
        render_rankBoard();
    }
}
void EndScene::clean()
{
    /* 写入rank file*/
    write_rankFile();
}
void EndScene::handle_event(SDL_Event *event)
{
    if (typing_flag) /* 玩家名称输入*/
    {
        if (event->type == SDL_TEXTINPUT)
        {
            name += event->text.text;
        }
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_RETURN)
            {
                typing_flag = false;
                SDL_StopTextInput();
                if (name.empty())
                {
                    /* 添加空玩家名称*/
                    name = "None";
                }
                /* 插入分数排行榜*/
                insert_rankBoard(hud_state.score, name);
            }
            if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
            {
                if (!name.empty())
                {
                    remove_lastUTF8Char(name);
                }
            }
        }
    }
    else /* 排行榜*/
    {
        if (event->type == SDL_KEYDOWN)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_J)
            {
                /* 清空hud_state*/
                hud_state = HudState{};
                get_game().get_hud().get_hudState() = hud_state;
                get_game().change_sceneNow(std::make_unique<MainScene>());
            }
        }
    }
}
void EndScene::render_textTyping()
{
    /* 渲染结束文字*/
    SDL_Color color{255, 255, 255, 255};
    std::string text;
    text = "你的得分是: " + std::to_string(hud_state.score);
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Small, color, 0.3);
    text = "Game Over";
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Medium, color, 0.4);
    text = "请输入你的名字, 按回车键退出: ";
    SDL_Point text_point = get_game().RenderTextCenterW(text, GameManager::NormalFontType::Small, color, 0.5);

    std::string cursor_text = "_";
    /* 渲染用户输入名称*/
    if (!name.empty())
    {
        SDL_Point name_point = get_game().RenderTextCenterW(name, GameManager::NormalFontType::Small, color, 0.6);
        if (timer < 500)
        {
            /* 闪烁绘制光标*/
            get_game().RenderTextPoint(cursor_text, GameManager::NormalFontType::Small, color, name_point);
        }
    }
    else
    {
        if (timer < 500)
        {
            /* 闪烁绘制光标*/
            get_game().RenderTextPoint(cursor_text, GameManager::NormalFontType::Small, color, text_point);
        }
    }
}
void EndScene::render_rankBoard()
{
    std::string text = "得分榜";
    SDL_Color color{255, 255, 255, 255};
    get_game().RenderTextCenterW(text, GameManager::NormalFontType::Large, color, 0.1);
    float height_percent = 0.15;
    int i = 1;
    for (auto item : rank_board)
    {
        std::string name = std::to_string(i) + ". " + item.second;
        std::string score = std::to_string(item.first);
        std::string text = name + "     " + score;
        get_game().RenderTextCenterW(text, GameManager::NormalFontType::Small, color, height_percent + i * 0.05);
        i++;
    }
    if (timer < 500)
    {
        std::string regame_text = "按 J 重新开始游戏!";
        get_game().RenderTextCenterW(regame_text, GameManager::NormalFontType::Medium, color, 0.8);
    }
}
/**
 * @brief: 正确退格utf-8字符
 */
void EndScene::remove_lastUTF8Char(std::string &str)
{
    auto lastchar = str.back();
    if ((lastchar & 0b10000000) == 0b10000000)
    {
        str.pop_back();
        while ((str.back() & 0b11000000) != 0b11000000)
        {
            str.pop_back();
        }
    }
    str.pop_back();
}
/**
 * @brief: 插入键值对到排行榜
 */
void EndScene::insert_rankBoard(int score, std::string name)
{
    rank_board.insert({score, name});
    if (rank_board.size() > SPACESHOOT_RANK_BOARD_MAX_ITEM)
    {
        auto it = std::prev(rank_board.end());
        rank_board.erase(it);
    }
}
/**
 * @brief: 写入排行榜到文件
 */
void EndScene::write_rankFile()
{
    std::ofstream rank_file(SPACESHOOT_RANK_BOARD_FILE_PATH);
    if (!rank_file.is_open())
    {
        std::cerr << "Write rank board file open failed." << std::endl;
        return;
    }
    for (const auto &item : rank_board)
    {
        rank_file << item.first << "," << item.second << std::endl;
    }
    rank_file.close();
}
/**
 * @brief: 读取排行榜文件
 */
void EndScene::read_rankFile()
{
    std::ifstream rank_file(SPACESHOOT_RANK_BOARD_FILE_PATH);
    if (!rank_file.is_open())
    {
        std::cerr << "Read rank board file open failed." << std::endl;
        return;
    }
    /* 清空rank_board*/
    rank_board.clear();
    std::string line;
    while (std::getline(rank_file, line))
    {
        /* 空行检测*/
        if (line.empty())
        {
            continue;
        }
        auto comma = line.find(',');
        /* 无逗号异常行检测*/
        if (comma == std::string::npos)
        {
            continue;
        }
        int score = 0;
        try
        {
            score = std::stoi(line.substr(0, comma));
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid score in rank file: " << e.what() << std::endl;
            continue;
        }
        std::string name = line.substr(comma + 1);
        /* 插入到rank_board*/
        rank_board.insert({score, name});
    }
    rank_file.close();
}