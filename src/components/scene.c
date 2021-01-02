#include "gameObject.h"
#include "gfx_manager.h"

scene* scene_new(game* game, void(*init)(struct game*)){
    scene* s = (scene*)malloc(sizeof(scene));
    s->gameObjects = vector_new();
    s->__game = game;
    s->deltatime = &game->delta_time;
    s->__timescale = 1;
    s->init = init;
    s->started = false;
    s->draw_mgr = gfxmgr_new();
    //s->index = vector_size(game->scenes);
    return s;
}

void scene_init(scene* scene){
    scene->init(scene->__game);
    //sort items by z-index for drawing
}

void scene_update(scene* scene){
    //call update on every gameOBJ in the scene
    for (uint i = 0; i < vector_size(scene->gameObjects); i++)
    {
        gameObject* go = vector_at(scene->gameObjects, i);
        gameObject_update(go);
    }
}

void scene_draw(scene* scene){
    for (uint i = 0; i < vector_size(scene->draw_mgr->drawables); i++)
    {
        sprite* s = vector_at(scene->draw_mgr->drawables, i);
        SDL_RenderCopy(s->game_renderer, s->texture, s->frames == 0 ? NULL : &s->src_rect, &s->dst_rect);
    }
}

float delta_time(scene* scene){
    return *scene->deltatime * scene->__timescale;;
}

float unscaled_delta_time(scene* scene){
    return *scene->deltatime;
}

void set_timescale(scene* scene, float timescale){
    scene->__timescale = timescale;
}
