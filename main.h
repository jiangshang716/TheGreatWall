#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 450
#define SCREEN_BPP 32
#define FRAMES_PER_SEC 30
#define ENEMY_NUM 5
#define ENEMY_SPEED 20



int GAME_LEVEL;
int apear_enemy;
int score;
int final_score;
int shoot_time;
int beat;
SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *message;
TTF_Font *font;
typedef struct {
	int alive;
	int facing;
	int x, y;
	SDL_Surface *image;
} Object;

Object player;
Object bullet;
Object enemy;
SDL_Event event;

#endif
