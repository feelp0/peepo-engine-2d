#include "components.h"
#include "gfx_manager.h"

// void sprite_new(component* comp, const char* path, int width, int height){
//     sprite* s = (sprite*)malloc(sizeof(sprite));
//     s->texture = NULL;
//     s->game_renderer = comp->owner->__game->__renderer;
//     SDL_Surface* surf = IMG_Load("resources/test.png");
//     s->rect.w = width == 0 ? surf->w : width;
//     s->rect.h = height == 0 ? surf->h : height;
//     //int a = IMG_Init(IMG_INIT_PNG | SDL_INIT_VIDEO);
//     s->texture = IMG_LoadTexture(s->game_renderer, "resources/test.png");
//     transform* t = (transform*)gameObject_get_component(comp->owner, TRANSFORM_T);
//     s->transform = t;
//     comp->data = s;
//     comp->init = sprite_init;
//     comp->update = sprite_update;
// }

void sprite_new(component* comp, const char* path, int z_index, int w, int h){
    sprite* s = (sprite*)malloc(sizeof(sprite));
    s->texture = NULL;
    s->game_renderer = comp->owner->__scene->__game->__renderer;
    SDL_Surface* surf = IMG_Load(path);
    s->dst_rect.w = w == 0 ? surf->w : w;
    s->dst_rect.h = h == 0 ? surf->h : h;
    s->z_index = z_index;
    s->frames = 0; //this is done to avoid errors
    //int a = IMG_Init(IMG_INIT_PNG | SDL_INIT_VIDEO);
    s->texture = IMG_LoadTexture(s->game_renderer, path);
    transform* t = (transform*)gameObject_get_component(comp->owner, TRANSFORM_T);
    s->transform = t;
    comp->data = s;
    comp->init = sprite_init;
    comp->update = sprite_update;
    comp->type = SPRITE_T;

    if(comp->owner->__scene->started)
        add_runtime_drawable(comp->owner->__scene->draw_mgr, s);
    else
        add_drawable(comp->owner->__scene->draw_mgr, s);
}

void sprite_new_animated(component* comp, const char* path, int z_index, int frames, float animationSpeed){
    sprite* s = (sprite*)malloc(sizeof(sprite));
    s->texture = NULL;
    s->game_renderer = comp->owner->__scene->__game->__renderer;
    SDL_Surface* surf = IMG_Load(path);
    s->frames = frames;
    s->curr_frame = 0;
    s->z_index = z_index;
    s->dst_rect.w = surf->w / s->frames;
    s->dst_rect.h = surf->h;
    s->animationSpeed = animationSpeed;
    s->__animationTimer = 0;
    s->surf = surf;
    
    s->src_rect.w = surf->w / s->frames;
    s->src_rect.h = surf->h;
    s->src_rect.x = 0;
    s->src_rect.y = 0;

    //int a = IMG_Init(IMG_INIT_PNG | SDL_INIT_VIDEO);
    s->texture = IMG_LoadTexture(s->game_renderer, path);
    transform* t = (transform*)gameObject_get_component(comp->owner, TRANSFORM_T);
    s->transform = t;
    comp->data = s;
    comp->init = sprite_init;
    comp->update = sprite_update;
    comp->type = SPRITE_T;

    if(comp->owner->__scene->started)
        add_runtime_drawable(comp->owner->__scene->draw_mgr, s);
    else
        add_drawable(comp->owner->__scene->draw_mgr, s);
}


void sprite_destroy(sprite* s){
    //r->game_renderer = NULL;
    SDL_DestroyTexture(s->texture);
    SDL_FreeSurface(s->surf);
    IMG_Quit();
    free(s);
}

void sprite_init(){
    
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