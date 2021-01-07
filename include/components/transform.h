#ifndef TRANSFORM_COMP
#define TRANSFORM_COMP
#include "gameObject.h"

struct transform {
    vec2 pos;
    vec2 rot;
}; typedef struct transform transform;

transform* transform_new(gameObject* go);
transform* transform_new_with_coord(gameObject* go, vec2 v);
void transform_update(component* c); //lallero
void transform_init(component* comp);
void transform_destroy(component* comp);
void transform_on_enable(component* comp);
void transform_on_disable(component* comp);

#endif