#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "game.h"

enum comp_type{
    SPRITE_T,
    BUTTON_T,
    PLAYER_T,
    TRANSFORM_T
}; typedef enum comp_type component_type;

typedef struct {
    vec2 pos;
    vector* components;
    scene* __scene;
} gameObject;

struct component{
    gameObject* owner;
    component_type type;
    void* data;
    void(*init)();
    void(*update)(struct component*);
} ; typedef struct component component;

gameObject* gameObject_new(scene* game);
gameObject* gameObject_new_default(scene* game);
void gameObject_destroy(gameObject* go);
component* gameObject_create_component(gameObject* go);
void* gameObject_get_component(gameObject* go, component_type ct);
void gameObject_update(gameObject* go);

component* __component_new(gameObject* go);

#endif