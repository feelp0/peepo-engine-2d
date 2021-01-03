#include "physics_manager.h"

physics_mgr* physics_mgr_new(){
    physics_mgr* p = (physics_mgr*)malloc(sizeof(physics_mgr));
    p->udatables = vector_new();
    return p;
}

void physics_mgr_update(physics_mgr* pm){
    int size = vector_size(pm->udatables);
    if(size <= 1) return;
    for (uint i = 0; i < size; i++)
    {
        circle_collider* cc1 = (circle_collider*)vector_at(pm->udatables, i);
        for (uint j = i + 1; j < size; j++)
        {
            circle_collider* cc2 = (circle_collider*)vector_at(pm->udatables, j);
            if(cc1 == cc2) continue;
            float vector_dist = vec2_dist(&cc1->position, &cc2->position);
            printf("vector dist is %f\n", vector_dist);
            float radiuses = cc1->radius + cc2->radius;
            if(vector_dist <= radiuses){
                cc1->onEnter(cc2->__collisionRef);
                cc2->onEnter(cc1->__collisionRef);
            }
        }
        
    }
    
}

void physics_mgr_add_updatable(physics_mgr* pm, circle_collider* updatable){
    vector_add(pm->udatables, updatable);
}
