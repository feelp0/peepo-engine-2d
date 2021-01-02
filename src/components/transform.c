#include "transform.h"

transform* transform_new(component* c){
    return transform_new_with_coord(c, 0.f,0.f);
}

transform* transform_new_with_coord(component* c, float x, float y){
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