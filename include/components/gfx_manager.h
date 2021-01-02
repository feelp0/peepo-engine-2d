#ifndef GFXMGR_H
#define GFXMGR_H
#include "vector.h"
#include "sprite.h"

struct gfxmgr{
    vector* drawables; //sprites
    vector* __drawables_z; //int (z-index)
}; typedef struct gfxmgr gfxmgr;

gfxmgr* gfxmgr_new();
int z_buffer(sprite* s1, sprite* s2);
void add_drawable(gfxmgr* gfxmgr, sprite* drawable_item);
void add_runtime_drawable(gfxmgr* gfxmgr, sprite* drawable_item);

#endif