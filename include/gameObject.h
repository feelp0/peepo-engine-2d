#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "game.h"

enum comp_type{
    SPRITE_T,
    PLAYER_T,
    TRANSFORM_T
}; typedef enum comp_type component_type;

typedef struct {
    vec2 pos;
    vector* components;
    game* __game;
} gameObject;

struct component{
    gameObject* owner;
    component_type type;
    void* data;
    void(*init)();
    void(*update)(struct component*);
} ; typedef struct component component;

gameObject* gameObject_new(game* game);
gameObject* gameObject_new_default(game* game);
void gameObject_destroy(gameObject* go);
component* gameObject_create_component(gameObject* go);
void* gameObject_get_component(gameObject* go, component_type ct);
void gameObject_update(gameObject* go);

component* __component_new(gameObject* go);

#endif