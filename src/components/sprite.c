#include "components.h"
#include "gfx_manager.h"

sprite* __sprite_create_def(gameObject* go, const char* path, int z_index){
    sprite* s = (sprite*)malloc(sizeof(sprite));
    component* comp = __component_new(go);
    s->texture = NULL;
    s->z_index = z_index;
    s->game_renderer = comp->owner->__scene->__game->__renderer;
    SDL_Surface* surf = IMG_Load(path);
    s->surf = surf;

    s->texture = IMG_LoadTexture(s->game_renderer, path);
    transform* t = (transform*)gameObject_get_component(comp->owner, TRANSFORM_T);
    s->transform = t;

    comp->data = s;
    comp->init = sprite_init;
    comp->update = sprite_update;
    comp->destroy = sprite_destroy;
    comp->type = SPRITE_T;

    if(comp->owner->__scene->started)
        add_runtime_drawable(comp->owner->__scene->draw_mgr, s);
    else
        add_drawable(comp->owner->__scene->draw_mgr, s);

    return s;
}

void sprite_new(gameObject* go, const char* path, int z_index, int w, int h){
    sprite* s = __sprite_create_def(go, path, z_index);
    s->dst_rect.w = w == 0 ? s->surf->w : w;
    s->dst_rect.h = h == 0 ? s->surf->h : h;
    s->frames = 0; //this is done to avoid errors
    SDL_FreeSurface(s->surf);
}

void sprite_new_animated(gameObject* go, const char* path, int z_index, int frames, float animationSpeed){
    sprite* s = __sprite_create_def(go, path, z_index);
    s->frames = frames;
    s->curr_frame = 0;
    s->dst_rect.w = s->surf->w / s->frames;
    s->dst_rect.h = s->surf->h;
    s->animationSpeed = animationSpeed;
    s->__animationTimer = 0;
    
    s->src_rect.w = s->surf->w / s->frames;
    s->src_rect.h = s->surf->h;
    s->src_rect.x = 0;
    s->src_rect.y = 0;
    SDL_FreeSurface(s->surf);
}

void sprite_destroy(component* comp){
    sprite* s = (sprite*)comp->data;
    remove_drawable(comp->owner->__scene->draw_mgr, s);
    SDL_DestroyTexture(s->texture);
    free(s);
}

void sprite_init(component* comp){
    
}

void sprite_update(component* c){
    sprite* s = (sprite*)c->data;
    if(s->frames != 0){
        s->__animationTimer += delta_time(c->owner->__scene);
        if(s->__animationTimer >= s->animationSpeed){
            s->curr_frame++;
            if(s->curr_frame >= s->frames){
                s->src_rect.x = 0;
                s->curr_frame = 0;
            }
            else
                s->src_rect.x += s->dst_rect.w;
           
            s->__animationTimer -= s->animationSpeed;
        }
    }
    s->dst_rect.x = s->transform->pos.x;
    s->dst_rect.y = s->transform->pos.y;
}

void sprite_scale(sprite* s, int value){
    s->dst_rect.w += value;
    s->dst_rect.h += value;
    s->transform->pos.x -= value * 0.5f;
    s->transform->pos.y -= value * 0.5f;
}

void sprite_recolor(sprite* s, uint r, uint g, uint b){
    SDL_SetTextureColorMod(s->texture, r, g, b);
}

void __sprite_enable(component* comp){

}

void __sprite_disable(component* comp){
    
}