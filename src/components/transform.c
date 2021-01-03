#include "transform.h"

transform* transform_new(gameObject* go){
    return transform_new_with_coord(go, 0.f,0.f);
}

transform* transform_new_with_coord(gameObject* go, float x, float y){
    component* c = __component_new(go);
    transform* t = (transform*)malloc(sizeof(transform));
    t->pos = vec2_new(x, y);
    c->data = t;
    c->type = TRANSFORM_T;
    c->init = transform_init;
    c->update = transform_update;
    c->destroy = transform_destroy;
    c->on_enable = transform_on_enable;
    c->on_disable = transform_on_disable;
    return t;
}

void transform_init(component* comp){
    
}

void transform_update(component* c){
    
}

void transform_destroy(component* comp){
    transform* t = (transform*)comp->data;
    free(t);
}

void transform_on_enable(component* comp){

}

void transform_on_disable(component* comp){

}