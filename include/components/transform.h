#ifndef TRANSFORM_COMP
#define TRANSFORM_COMP
#include "gameObject.h"

typedef struct{
    vec2 pos;
    vec2 rot;
}transform;

transform* transform_new(gameObject* go);
transform* transform_new_with_coord(gameObject* go, float x, float y);
void transform_update(component* c); //lallero
void transform_init();

#endif