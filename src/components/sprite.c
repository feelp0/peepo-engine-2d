#include "sprite.h"
//#include "SDL_image.h"

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

void sprite_new(component* comp, const char* path, int w, int h){
    sprite* s = (sprite*)malloc(sizeof(sprite));
    s->texture = NULL;
    s->game_renderer = comp->owner->__game->__renderer;
    SDL_Surface* surf = IMG_Load(path);
    s->rect.w = w == 0 ? surf->w : w;
    s->rect.h = h == 0 ? surf->h : h;
    //int a = IMG_Init(IMG_INIT_PNG | SDL_INIT_VIDEO);
    s->texture = IMG_LoadTexture(s->game_renderer, path);
    transform* t = (transform*)gameObject_get_component(comp->owner, TRANSFORM_T);
    s->transform = t;
    comp->data = s;
    comp->init = sprite_init;
    comp->update = sprite_update;
    comp->type = SPRITE_T;
}

void sprite_destroy(sprite* s){
    //r->game_renderer = NULL;
    SDL_DestroyTexture(s->texture);
    IMG_Quit();
    free(s);
}

void sprite_init(){
    
}

void sprite_update(component* c){
    sprite* s = (sprite*)c->data;
    //printf("rednererUpdate");
    s->rect.x = s->transform->pos.x;
    s->rect.y = s->transform->pos.y;
    SDL_RenderCopy(s->game_renderer, s->texture, NULL, &s->rect);
}