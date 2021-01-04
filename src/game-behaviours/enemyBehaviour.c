#include"components.h"

void enemy_new(gameObject* go, move_axis axis, float speed, float shootCooldown, int maxHealth){
    enemy_behaviour* e = (enemy_behaviour*)malloc(sizeof(enemy_behaviour));
    component* c = __component_new(go);
    e->axis = axis;
    e->__speed = speed;
    e->__shootCD = shootCooldown;
    e->__maxHealth = maxHealth;
    e->__currHealth = maxHealth;
    e->__bullets = vector_new_with_cap(20);
    c->data = e;
    c->init = enemy_init;
    c->update = enemy_update;
    c->destroy = enemy_destroy;
    c->on_enable = enemy_on_enable;
    c->on_disable = enemy_on_disable;
    c->type = ENEMY_T;
}

void enemy_init(component* comp){

}

void enemy_update(component* c){
    transform* t = (transform*)gameObject_get_component(c->owner, TRANSFORM_T);
    enemy_behaviour* p = (enemy_behaviour*)gameObject_get_component(c->owner, ENEMY_T);
    sprite* s = (sprite*)gameObject_get_component(c->owner, SPRITE_T);
    float dt = delta_time(c->owner->__scene);
    //t->pos.x -= 1.f * p->__speed * dt;
}

void enemy_destroy(component* comp){

}

void enemy_on_enable(component* comp){

}

void enemy_on_disable(component* comp){

}