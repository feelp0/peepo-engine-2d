#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "game.h"

enum comp_type{
    SPRITE_T,
    AUDIO_EMITTER_T,
    CIRCLE_COLLIDER_T,
    BUTTON_T,
    PLAYER_T,
    ENEMY_T,
    TRANSFORM_T
}; typedef enum comp_type component_type;

typedef struct {
    vec2 pos;
    vector* components;
    scene* __scene;
    boolean __dontDestroyOnLoad;
    boolean __is_active;
} gameObject;

struct component{
    gameObject* owner;
    component_type type;
    void* data;
    void(*init)(struct component*);
    void(*update)(struct component*);
    void(*destroy)(struct component*);
    void(*on_enable)(struct component*);
    void(*on_disable)(struct component*);
} ; typedef struct component component;

gameObject* gameObject_new(scene* scene);
gameObject* gameObject_new_with_coord(scene* scene, vec2* pos);
gameObject* gameObject_new_default(scene* scene);
void gameObject_destroy(gameObject* go);
void* gameObject_get_component(gameObject* go, component_type ct);
void gameObject_update(gameObject* go);
void dont_destroy_on_load(gameObject* go);
boolean gameObject_is_active(gameObject* go);
void gameObject_set_active(gameObject* go, boolean state);

component* __component_new(gameObject* go);

#endif