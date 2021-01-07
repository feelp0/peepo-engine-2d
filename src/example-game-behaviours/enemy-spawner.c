#include "components.h"

void enemy_spawner_new(gameObject* go, float spawnCD){
    enemy_spawner* e = (enemy_spawner*)malloc(sizeof(enemy_spawner));
    component* c = __component_new(go);
    e->spawnCD = spawnCD;
    e->__spawnTimer = 0;
    e->spawnNum = 1;
    e->__sprites = vector_new();
    vector_add(e->__sprites, "resources/assets/enemy/enemy1_strip3.png");
    vector_add(e->__sprites, "resources/assets/enemy/enemy2_strip3.png");
    vector_add(e->__sprites, "resources/assets/enemy/enemy3_strip3.png");
    vector_add(e->__sprites, "resources/assets/enemy/enemy4_strip3.png");

    e->enemies = createQueue();
    for (uint i = 0; i < 30; i++)
    {
        vec2 pos = vec2_new(-100, -100);
        vec2 dir = vec2_new(0,1);
        gameObject* enemy = gameObject_new_with_coord(go->__scene, "enemyTest", &pos);
        const char* lallero = "mammolo";
        const char* path = (const char*)vector_at(e->__sprites, (uint)GetRandomIntBetween(e->__sprites->__count - 1, 0));
        sprite_new_animated(enemy, path, 1, 3, 0.1f);
        enemy_new(enemy, dir, 100, 0, 3);
        circle_collider_new(enemy, 0, NULL, NULL, NULL);
        circle_collider_set_collision(enemy, ENEMY_MASK, PLAYER_MASK);
        gameObject_set_active(enemy, false);
        enqueue(e->enemies, enemy);
    }
    
    c->data = e;
    c->init = enemy_spawner_init;
    c->update = enemy_spawner_update;
    c->destroy = enemy_spawner_destroy;
    c->type = ENEMY_SPAWNER_T;

    e->__component = c;
}

void enemy_spawner_init(component* c){

}

void enemy_spawner_update(component* c){
    enemy_spawner* es = (enemy_spawner*)c->data;
    double dt = delta_time_sec(c->owner->__scene);
    es->__spawnTimer += dt;
    if(es->__spawnTimer >= es->spawnCD){

        for (int i = 0; i <= es->spawnNum; i++)
        {
            gameObject* go = dequeue(es->enemies);
            //enemy_behaviour* eb = (enemy_behaviour*)gameObject_get_component(go, ENEMY_T);
            vec2 p = vec2_new(GetRandomIntBetween(go->__scene->__game->width,0), -50);
            go->transform->pos = p;
            gameObject_set_active(go, true);
            enqueue(es->enemies, go);
        }
        es->__spawnTimer = 0;
    }
    
}

void enemy_spawner_destroy(component* c){

}
