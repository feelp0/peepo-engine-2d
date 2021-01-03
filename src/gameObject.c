#include "gameObject.h"

gameObject* gameObject_new(scene* scene){
    gameObject* go = (gameObject*)malloc(sizeof(gameObject));
    go->components = vector_new();
    go->__scene = scene;
    go->__dontDestroyOnLoad = false;
    go->__is_active = true;
    transform_new(go);
    vector_add(go->__scene->gameObjects, go);
    return go;
}

gameObject* gameObject_new_default(scene* scene){
    gameObject* go = (gameObject*)malloc(sizeof(gameObject));
    //go->pos = vec2_new(x, y);
    go->components = vector_new();
    //transform* t;
    go->__scene = scene;
    return go;
}

void gameObject_destroy(gameObject* go){
    for (uint i = 0; i < vector_size(go->components); i++)
    {
        component* c = vector_at(go->components, i);
        c->destroy(c);
    }
    vector_destroy(go->components);
    go->__scene = NULL;
    free(go);   
}

boolean gameObject_is_active(gameObject* go){
    return go->__is_active;
}

void gameObject_set_active(gameObject* go, boolean state){
    go->__is_active = state;
    //call OnEnable/OnDisable
}

void gameObject_update(gameObject* go){
    for (uint i = 0; i < vector_size(go->components); i++)
    {
        component* comp = (component*)vector_at(go->components, i);
        //comp->update(go->__game->delta_time);
        comp->update(comp);
    }
}

void* gameObject_get_component(gameObject* go, component_type ct){
    for (uint i = 0; i < vector_size(go->components); i++)
    {
        component* comp = (component*)vector_at(go->components, i);
        if(comp->type == ct){
            return comp->data;
        }
    }
    return NULL;
}

component* __component_new(gameObject* go){
    component* comp = (component*)malloc(sizeof(component));
    comp->owner = go;
    vector_add(go->components, comp);
    return comp;
}

void dont_destroy_on_load(gameObject* go){
    go->__dontDestroyOnLoad = true;
}