#include "components.h"

void player_new(gameObject* go, float speed, float shootCooldown, int maxHealth){
    playerBehaviour* p = (playerBehaviour*)malloc(sizeof(playerBehaviour));
    component* c = __component_new(go);
    p->__speed = speed;
    p->__shootCD = shootCooldown;
    p->__maxHealth = maxHealth;
    p->__currHealth = maxHealth;
    p->__bullets = vector_new_with_cap(20);
    c->data = p;
    c->init = player_init;
    c->update = player_update;
    c->type = PLAYER_T;
}

void player_init(){

}

void player_update(component* c){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    transform* t = (transform*)gameObject_get_component(c->owner, TRANSFORM_T);
    playerBehaviour* p = (playerBehaviour*)gameObject_get_component(c->owner, PLAYER_T);
    sprite* s = (sprite*)gameObject_get_component(c->owner, SPRITE_T);
    float dt = delta_time(c->owner->__scene);
    if(state[SDL_SCANCODE_LEFT]){
        if((int)t->pos.x > 0) //avoid exit from screen x < 0
            t->pos.x -= 1.f * p->__speed * dt;
    }
    if(state[SDL_SCANCODE_RIGHT]){
        if((int)t->pos.x < c->owner->__scene->__game->width - s->dst_rect.w) //avoid exit from screen x > window.w
            t->pos.x += 1.f * p->__speed * dt;
    }
    if(state[SDL_SCANCODE_UP]){
        if((int)t->pos.y > 0)
            t->pos.y -= 1.f * p->__speed * dt;
    }
    if(state[SDL_SCANCODE_DOWN]){
        t->pos.y += 1.f * p->__speed * dt;
    }
}