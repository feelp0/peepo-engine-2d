#ifndef ENEMY_BEHAVIOUR_H
#define ENEMY_BEHAVIOUR_H

enum move_axis {
    HORIZONTAL,
    VERTICAL
}; typedef enum move_axis move_axis;

struct enemy_behaviour{
    vec2 dir;
    float __speed;
    int __maxHealth;
    int __currHealth;
    float __shootCD;
    vector* __bullets;
    gameObject* __particles;
    component* __component;
};typedef struct enemy_behaviour enemy_behaviour;

void enemy_new(gameObject* go, vec2 dir, float speed, float shootCooldown, int maxHealth);
void enemy_init(component* comp);
void enemy_update(component* c);
void enemy_destroy(component* comp);
void enemy_on_enable(component* comp);
void enemy_on_disable(component* comp);
boolean enemy_on_damage(enemy_behaviour* eb, int damage);

#endif