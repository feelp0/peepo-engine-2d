#include "circle_collider.h"
#include "physics_manager.h"

void circle_collider_new(gameObject* go, float radius, void (*onEnter)(struct component*), void(*onExit)(struct component*)){
    circle_collider* cc = (circle_collider*)malloc(sizeof(circle_collider));
    cc->position = vec2_new(0, 0); //center of the object
    if(radius == 0){ //use sprite size
        sprite* s = (sprite*)gameObject_get_component(go, SPRITE_T);
        cc->radius = (float)s->dst_rect.w * 0.5f; //assuming it will be a squared image
    }
    else{
        cc->radius = radius;
    }
    cc->onEnter = onEnter;
    cc->onExit = onExit;
    cc->__active = true;
    cc->__t = (transform*)gameObject_get_component(go, TRANSFORM_T);

    component* comp = __component_new(go);
    comp->data = cc;
    comp->init = circle_collider_init;
    comp->update = circle_collider_update;
    comp->on_enable = circle_collider_on_enable;
    comp->on_disable = circle_collider_on_disable;
    comp->destroy = circle_collider_destroy;
    comp->type = CIRCLE_COLLIDER_T;

    cc->__collisionRef = comp;
    
    physics_mgr_add_updatable(go->__scene->physics_mgr, cc);
}

void circle_collider_init(component* comp){

}

void circle_collider_update(component* comp){
    circle_collider* cc = (circle_collider*)comp->data;
    //cc->position = vec2_add(&cc->__t->pos, &cc->position); //manage offset collider lmao im stupid. FIX THIS with a second offset
    cc->position = cc->__t->pos;
}

void circle_collider_on_enable(component* comp){
    circle_collider* cc = (circle_collider*)comp->data;
    cc->__active = true;
}

void circle_collider_on_disable(component* comp){
    circle_collider* cc = (circle_collider*)comp->data;
    cc->__active = false;
}

void circle_collider_destroy(component* comp){
    circle_collider* cc = (circle_collider*)comp->data;
    free(cc);
}
