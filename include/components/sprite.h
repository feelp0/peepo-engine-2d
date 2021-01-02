#ifndef SPRITE_H
#define SPRITE_H
#include "gameObject.h"
#include "transform.h"

struct sprite{
    SDL_Texture* texture;
    SDL_Renderer* game_renderer;
    SDL_Rect rect;
    transform* transform;
};typedef struct sprite sprite;

void sprite_new(component* comp, const char* path, int w, int h);
void sprite_destroy(sprite* r);
void sprite_init();
void sprite_update(component* c);

#endif