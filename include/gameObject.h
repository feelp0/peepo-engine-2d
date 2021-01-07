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
    ENEMY_SPAWNER_T,
    BULLET_T,
    TRANSFORM_T
}; typedef enum comp_type component_type;

struct transform;
struct gameObject{
    const char* name;
    vector* components;
    scene* __scene;
    struct transform* transform;
    boolean __dontDestroyOnLoad;
    boolean __is_active;
}; typedef struct gameObject gameObject;

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

gameObject* gameObject_new(scene* scene, const char* name);
gameObject* gameObject_new_with_coord(scene* scene, const char* name, vec2* pos);
void gameObject_destroy(gameObject* go);
void* gameObject_get_component(gameObject* go, component_type ct);
void gameObject_update(gameObject* go);
void dont_destroy_on_load(gameObject* go);
boolean gameObject_is_active(gameObject* go);
void gameObject_set_active(gameObject* go, boolean state);

component* __component_new(gameObject* go);

#endif