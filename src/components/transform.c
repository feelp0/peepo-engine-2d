#include "transform.h"

transform* transform_new(gameObject* go){
    return transform_new_with_coord(go, 0.f,0.f);
}

transform* transform_new_with_coord(gameObject* go, float x, float y){
    component* c = __component_new(go);
    c->init = transform_init;
    c->update = transform_update;
    transform* t = (transform*)malloc(sizeof(transform));
    t->pos = vec2_new(x, y);
    c->data = t;
    c->type = TRANSFORM_T;
    return t;
}

void transform_init(){
    
}

void transform_update(component* c){
    
}