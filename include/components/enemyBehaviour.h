#ifndef ENEMY_BEHAVIOUR_H
#define ENEMY_BEHAVIOUR_H

enum move_axis {
    HORIZONTAL,
    VERTICAL
}; typedef enum move_axis move_axis;

struct enemy_behaviour{
    move_axis axis;
    float __speed;
    int __maxHealth;
    int __currHealth;
    float __shootCD;
    vector* __bullets;
};typedef struct enemy_behaviour enemy_behaviour;

void enemy_new(gameObject* go, move_axis axis, float speed, float shootCooldown, int maxHealth);
void enemy_init(component* comp);
void enemy_update(component* c);
void enemy_destroy(component* comp);
void enemy_on_enable(component* comp);
void enemy_on_disable(component* comp);

#endif