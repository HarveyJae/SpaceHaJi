#ifndef __MAIN_H__
#define __MAIN_H__
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#define SPACESHOOT_IMG_FORMAT (IMG_INIT_JPG | IMG_INIT_PNG)                        /* 图片格式*/
#define SPACESHOOT_MIX_FREQUENCY MIX_DEFAULT_FREQUENCY                             /* 音频频率*/
#define SPACESHOOT_MIX_FORMAT MIX_DEFAULT_FORMAT                                   /* 音频格式*/
#define SPACESHOOT_MIX_CHANNELS MIX_DEFAULT_CHANNELS                               /* 音频通道*/
#define SPACESHOOT_MIX_VOLUME MIX_MAX_VOLUME                                       /* 音频音量*/
#define SPACESHOOT_MIX_BUFFER_SIZE 2048                                            /* 音频输出缓冲区大小*/
#define SPACESHOOT_IMG_PATH_BG "assets/image/bg.png"                               /* 背景图片路径*/
#define SPACESHOOT_MIX_PATH_BG "assets/music/03_Racing_Through_Asteroids_Loop.ogg" /* 背景音频路径*/
#define SPACESHOOT_TTF_PATH_BG "assets/font/VonwaonBitmap-16px.ttf"                /* 背景字体路径*/
#define SPACESHOOT_TTF_SIZE_BG 24                                                  /* 背景字体大小*/
#endif