#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "vec2.h"
#include "vector.h"
#include "common.h"
//#include "gameObject.h"
#include "scene.h"

struct game{
    int width;
    int height;
    int __last_count;
    int __curr_count;
    int __frequency;
    int mouseState;
    float delta_time;
    vector* scenes;
    scene* current_scene;
    scene* next_scene;
    SDL_Window* __window;
    SDL_Renderer* __renderer;
    Uint8* vkey;
    boolean running;
}; typedef struct game game; 

game* game_new(int width, int height);
//void add_gameObject(game* game, gameObject* go);
int init(game* game);
void gameLoop(game* game);
void input(game* game);
void tick(game* game);
void clear(game* game);
void update(game* game);
void draw(game* game);

#endif