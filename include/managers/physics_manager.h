#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include "components.h"
#include "list.h"

struct physics_mgr{
    vector* udatables;
    vector* collisions;
};typedef struct physics_mgr physics_mgr;

struct collision{
    circle_collider* cc1;
    circle_collider* cc2;
    int index;
}; typedef struct collision collision;

physics_mgr* physics_mgr_new();
void physics_mgr_update(physics_mgr* pm);
void physics_mgr_add_updatable(physics_mgr* pm, struct circle_collider* item);
void physics_mgr_remove_updatable(physics_mgr* pm, struct circle_collider* item);
void physics_mgr_add_collision(physics_mgr* pm, circle_collider* cc1, circle_collider* cc2);

//collision collision_new(circle_collider* cc1, circle_collider* cc2);

#endif