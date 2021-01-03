#include "gfx_manager.h"

gfxmgr* gfxmgr_new(){
    gfxmgr* g = (gfxmgr*)malloc(sizeof(gfxmgr));
    g->drawables = vector_new();
    return g;
}

int z_buffer(sprite* s1, sprite* s2){
    if(s1->z_index > s2->z_index) return 1;
    else if(s1->z_index < s2->z_index) return -1;
    return 0;
}

void add_runtime_drawable(gfxmgr* gfxmgr, sprite* drawable_item){
    add_drawable(gfxmgr, drawable_item);
    vector_quick(gfxmgr->drawables, z_buffer);
}

void add_drawable(gfxmgr* gfxmgr, sprite* drawable_item){
    int size = vector_size(gfxmgr->drawables);
    if(size == 0){
        vector_add(gfxmgr->drawables, drawable_item);
        return;
    }
    vector_add(gfxmgr->drawables, drawable_item);
}

void remove_drawable(gfxmgr* gfxmgr, sprite* drawable_item){
    vector_remove(gfxmgr->drawables, drawable_item);
}

void gfxmgr_destroy(gfxmgr* gfxmgr){
    vector_destroy(gfxmgr->drawables);
    free(gfxmgr);
}

void gfxmgr_draw(gfxmgr* gfxmgr){
    // for (uint i = 0; i < vector_size(gfxmgr->drawables); i++)
    // {
    //     sprite* s = vector_at(gfxmgrs->drawables, i);
    //     SDL_RenderCopy(s->game_renderer, s->texture, s->frames == 0 ? NULL : &s->src_rect, &s->dst_rect);
    // }
}