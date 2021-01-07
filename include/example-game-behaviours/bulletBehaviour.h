#ifndef BULLET_BHEAVIOUR_H
#define BULLET_BHEAVIOUR_H
//#include "gameObject.h"

struct bulletBehaviour
{
    float speed;
    int damage;
    gameObject* owner;
    vec2 dir;
    vec2 __cannon_pivot;
    transform* transform;
}; typedef struct bulletBehaviour bullet;


bullet* bullet_new(gameObject* go, gameObject* owner, float speed, int damage, vec2 dir, vec2 cannon_pivot);
void bullet_init(component* comp);
void bullet_update(component* comp);
void bullet_destroy(component* comp);
void bullet_on_enable(component* comp);
void bullet_on_disable(component* comp);

void bullet_on_enter(component* me, component* other);

#endif