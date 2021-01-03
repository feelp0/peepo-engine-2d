#ifndef PLAYERBEHAVIOUR_H
#define PLAYERBEHAVIOUR_H
#include "gameObject.h"

struct playerBehaviour{
    float __speed;
    int __maxHealth;
    int __currHealth;
    float __shootCD;
    vector* __bullets;
}; typedef struct playerBehaviour playerBehaviour;

void player_new(gameObject* go, float speed, float shootCooldown, int maxHealth);
void player_init();
void player_update(component* c);


#endif