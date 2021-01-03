#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "game.h"

struct scene{
    const char* scene_name;
    int index;
    float* deltatime;
    float __timescale;
    struct game* __game;
    struct gfxmgr* draw_mgr;
    struct physics_mgr* physics_mgr;
    vector* gameObjects;
    boolean started;
    void(*init)(struct game*);
}; typedef struct scene scene;

scene* scene_new();
void scene_init();
void scene_update(scene* scene);
void scene_draw(scene* scene);
void scene_set_active(scene* s);
scene* scene_get_by_index(struct game* game, int index);
scene* scene_get_by_name(struct game* game, const char* name);
float delta_time(scene* scene);
float unscaled_delta_time(scene* scene);
void set_timescale(scene* scene, float timescale);
void scene_change(scene* old_scene, scene* new_scene);
void scene_destroy(scene* scene);

#endif