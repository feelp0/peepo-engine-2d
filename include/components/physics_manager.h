#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include "components.h"

struct physics_mgr{
    vector* udatables;
};typedef struct physics_mgr physics_mgr;

physics_mgr* physics_mgr_new();
void physics_mgr_update(physics_mgr* pm);
void physics_mgr_add(physics_mgr* pm, struct circle_collider* item);

#endif