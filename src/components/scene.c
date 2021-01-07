#include "gameObject.h"
#include "gfx_manager.h"
#include "physics_manager.h"

scene* scene_new(game* game, const char* name, void(*init)(struct game*)){
    scene* s = (scene*)malloc(sizeof(scene));
    s->gameObjects = vector_new();
    s->__game = game;
    s->scene_name = name;
    s->deltatime = &game->delta_time;
    s->__timescale = 1;
    s->init = init;
    s->started = false;
    s->draw_mgr = gfxmgr_new(s->__game->__renderer);
    s->physics_mgr = physics_mgr_new();
    s->index = vector_size(s->__game->scenes);
    vector_add(s->__game->scenes, s);
    //s->index = vector_size(game->scenes);
    return s;
}

void scene_set_active(scene* s){
    s->__game->current_scene = s;
    s->__game->next_scene = s->__game->current_scene;
}

scene* scene_get_by_index(game* game, int index){
    return vector_at(game->scenes, index);
}

scene* scene_get_by_name(game* game, const char* name){
    for (uint i = 0; i < vector_size(game->scenes); i++)
    {
        scene* s = vector_at(game->scenes, i);
        if(s->scene_name == name){
            return s;
        }
    }
    return NULL;
}

void scene_init(scene* scene){
    printf("init-scene");
    scene->init(scene->__game);
    //sort items by z-index for drawing
}

void scene_update(scene* scene){
    //call update on every gameOBJ in the scene
    for (uint i = 0; i < vector_size(scene->gameObjects); i++)
    {
        gameObject* go = vector_at(scene->gameObjects, i);
        if(gameObject_is_active(go))
            gameObject_update(go);
    }
    
    physics_mgr_update(scene->physics_mgr);
}

void scene_draw(scene* scene){
    gfxmgr_draw(scene->draw_mgr);
}

void scene_destroy(scene* scene){
    vector_destroy(scene->gameObjects);
    gfxmgr_destroy(scene->draw_mgr);
    free(scene);
}

void scene_change(scene* old_scene, scene* new_scene){
    for (uint i = 0; i < vector_size(old_scene->gameObjects); i++)
    {
        gameObject* go = vector_at(old_scene->gameObjects, i);
        if(go->__dontDestroyOnLoad){
            vector_remove_at(old_scene->gameObjects, i);
            vector_add(new_scene->gameObjects, go);
            //i--;
        }
        else{
            gameObject_destroy(go);
        }
    }
    old_scene->__game->current_scene = new_scene;
    scene_destroy(old_scene);
}

double delta_time_sec(scene* scene){
    double dt = (*scene->deltatime * 0.001);
    return dt;
}

double delta_time(scene* scene){
    return *scene->deltatime * scene->__timescale;
}

double unscaled_delta_time(scene* scene){
    return *scene->deltatime;
}

void set_timescale(scene* scene, float timescale){
    scene->__timescale = timescale;
}
