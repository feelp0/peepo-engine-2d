#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H
#include "components.h"

struct circle_collider{
    float radius;
    vec2 position;
    transform* __t;
    void (*onEnter)(struct component*);
    void (*onExit)(struct component*);
    void (*onStay)(struct component*);
    boolean __active;
    vector* insideObjs;
    struct component* __collisionRef;
}; typedef struct circle_collider circle_collider;

void circle_collider_new(gameObject* go,float radius, void (*onEnter)(struct component*), void (*onStay)(struct component*), void (*onExit)(struct component*));
void circle_collider_init(component* comp);
void circle_collider_update(component* comp);
void circle_collider_on_enable(component* comp);
void circle_collider_on_disable(component* comp);
void circle_collider_destroy(component* comp);

void __cc_add_colliding_obj(component* me, component* other);
void __cc_remove_colliding_obj(component* me, component* other);

#endif