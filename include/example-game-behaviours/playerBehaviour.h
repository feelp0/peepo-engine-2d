#ifndef PLAYERBEHAVIOUR_H
#define PLAYERBEHAVIOUR_H
#include "gameObject.h"

struct playerBehaviour{
    float __speed;
    int __maxHealth;
    int __currHealth;
    float __shootCD;
    float __shootTimer;
    queue* __bullets;
}; typedef struct playerBehaviour playerBehaviour;

void player_new(gameObject* go, float speed, float shootCooldown, int maxHealth);
void player_init(component* comp);
void player_update(component* c);
void player_destroy(component* comp);
void player_on_enable(component* comp);
void player_on_disable(component* comp);

#endif