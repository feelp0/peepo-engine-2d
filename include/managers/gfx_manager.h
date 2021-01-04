#ifndef GFXMGR_H
#define GFXMGR_H
#include "vector.h"
#include "sprite.h"

struct gfxmgr{
    vector* drawables; //sprites
    SDL_Renderer* game_renderer;
}; typedef struct gfxmgr gfxmgr;

gfxmgr* gfxmgr_new();
void gfxmgr_destroy(gfxmgr* gfxmgr);
int z_buffer(sprite* s1, sprite* s2);
void add_drawable(gfxmgr* gfxmgr, sprite* drawable_item);
void remove_drawable(gfxmgr* gfxmgr, sprite* drawable_item);
void add_runtime_drawable(gfxmgr* gfxmgr, sprite* drawable_item);
void gfxmgr_draw(gfxmgr* gfxmgr);

#endif