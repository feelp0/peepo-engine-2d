#ifndef SCENE_H
#define SCENE_H
#include "vector.h"
#include "game.h"

struct scene{
    int index;
    float* deltatime;
    float __timescale;
    struct game* __game;
    struct gfxmgr* draw_mgr;
    vector* gameObjects;
    boolean started;
    void(*init)(struct game*);
}; typedef struct scene scene;

scene* scene_new();
void scene_init();
void scene_update(scene* scene);
void scene_draw(scene* scene);
float delta_time(scene* scene);
float unscaled_delta_time(scene* scene);
void set_timescale(scene* scene, float timescale);

#endif