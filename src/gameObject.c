#include "gameObject.h"

gameObject* gameObject_new(game* game){
    gameObject* go = (gameObject*)malloc(sizeof(gameObject));
    go->components = vector_new();
    go->__game = game;
    component* comp = __component_new(go);
    transform_new(comp);
    vector_add(go->components, comp);
    return go;
}

gameObject* gameObject_new_default(game* game){
    gameObject* go = (gameObject*)malloc(sizeof(gameObject));
    //go->pos = vec2_new(x, y);
    go->components = vector_new();
    //transform* t;
    go->__game = game;
    return go;
}

void gameObject_destroy(gameObject* go){
    vector_destroy(go->components);
    go->__game = NULL;
    free(go);   
}

// void gameObject_add_component(gameObject* go, component* comp){
//     vector_add(go->components, comp);
// }

component* gameObject_create_component(gameObject* go){
    component* comp = __component_new(go); // create base default component
    return comp;
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