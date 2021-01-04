#include "physics_manager.h"

physics_mgr* physics_mgr_new(){
    physics_mgr* p = (physics_mgr*)malloc(sizeof(physics_mgr));
    p->udatables = vector_new();
    p->collisions = vector_new();
    return p;
}

boolean __check_circle_collision(circle_collider* cc1, circle_collider* cc2){
    float vector_dist = vec2_dist(&cc1->position, &cc2->position);
    //printf("dist: %f\n", vector_dist);
    float radiuses = cc1->radius + cc2->radius;
    if(vector_dist <= radiuses) return true;
    return false;
}


void physics_mgr_collisions_update(physics_mgr* pm){
    int size = (int)vector_size(pm->collisions);
    for (int i = size - 1; i >= 0; i--)
    {
        collision* c = (collision*)vector_at(pm->collisions, i);
        if(!__check_circle_collision(c->cc1, c->cc2)){
            // if(c->cc1->onExit != NULL) c->cc1->onExit(c->cc2->__collisionRef);
            // if(c->cc2->onExit != NULL) c->cc2->onExit(c->cc1->__collisionRef);
            __cc_remove_colliding_obj(c->cc1->__collisionRef, c->cc2->__collisionRef);
            __cc_remove_colliding_obj(c->cc2->__collisionRef, c->cc1->__collisionRef);
            vector_remove(pm->collisions, c);
        }
    }
}

void physics_mgr_update(physics_mgr* pm){
    int size = vector_size(pm->udatables);
    if(size <= 1) return;
    //check for new collision and call on stay if needed
    for (uint i = 0; i < size; i++)
    {
        circle_collider* cc1 = (circle_collider*)vector_at(pm->udatables, i);
        for (uint j = i + 1; j < size; j++)
        {
            circle_collider* cc2 = (circle_collider*)vector_at(pm->udatables, j);
            if(cc1 == cc2) continue;
            //printf("vector dist is %f\n", vector_dist);
            if(__check_circle_collision(cc1, cc2)){
                __cc_add_colliding_obj(cc1->__collisionRef, cc2->__collisionRef);
                __cc_add_colliding_obj(cc2->__collisionRef, cc1->__collisionRef);
            }
        }
    }
    
    //check state of existing collision
    physics_mgr_collisions_update(pm);
}

void physics_mgr_add_updatable(physics_mgr* pm, circle_collider* updatable){
    vector_add(pm->udatables, updatable);
}

boolean __check_existing_collision(physics_mgr* pm, collision* c1){ //TODO: this sucks but atm works. find another way to avoid adding same collision
    for (uint i = 0; i < pm->collisions->__count; i++)
    {
        collision* c2 = (collision*)vector_at(pm->collisions, i);
        if(c1 == c2) return true;
        else if((c1->cc1 == c2->cc1 && c1->cc2 == c2->cc2) || (c1->cc1 == c2->cc2 && c1->cc2 == c2->cc1)) return true;
    }
    return false;
} 

void physics_mgr_add_collision(physics_mgr* pm, circle_collider* cc1, circle_collider* cc2){
    collision* c = (collision*)malloc(sizeof(collision));
    c->cc1 = cc1;
    c->cc2 = cc2;
    if(!__check_existing_collision(pm, c))
        vector_add(pm->collisions, c);
}
