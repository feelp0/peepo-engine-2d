#ifndef SPRITE_H
#define SPRITE_H
#include "gameObject.h"
#include "transform.h"

struct sprite{
    SDL_Texture* texture;
    SDL_Surface* surf;
    SDL_Rect dst_rect;
    SDL_Rect src_rect;
    transform* transform;
    int z_index;
    int frames;
    int curr_frame;
    float animationSpeed;
    float __animationTimer;
    boolean __active;
};typedef struct sprite sprite;

void sprite_new(gameObject* go, const char* path, int z_index, int w, int h);
void sprite_new_animated(gameObject* go, const char* path, int z_index, int frames, float animationSpeed);
void sprite_destroy(component* comp);
void sprite_init(component* comp);
void sprite_update(component* c);
void sprite_scale(sprite* s, int value);
void sprite_recolor(sprite* s, uint r, uint g, uint b);

void sprite_enable(component* comp);
void sprite_disable(component* comp);

#endif