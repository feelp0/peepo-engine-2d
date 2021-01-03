#include "gameObject.h"
#include "components.h"
#include "gfx_manager.h"

game* game_new(int width, int height){
    game* g = malloc(sizeof(game));
    g->width = width;
    g->height = height;
    g->scenes = vector_new();
    g->running = true;
    g->mouseState = 0;
    g->__curr_count = (int)SDL_GetPerformanceCounter();
    g->__last_count = g->__curr_count;
    init(g);
    return g;
}

int init(game* game){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);

    game->__window = SDL_CreateWindow(
        "First SDL Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->width, game->height,
        0
    );
    if(game->__window == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "Could not create window: %s", SDL_GetError());
        return 1;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
    else
    {
        //Get window surface
        SDL_GetWindowSurface(game->__window);
    }

    game->__renderer = SDL_CreateRenderer(game->__window, -1, SDL_RENDERER_ACCELERATED);
    if(game->__renderer == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "Could not create renderer: %s", SDL_GetError());
        return 2;
    }
    
    SDL_SetWindowTitle(game->__window, "peepo-engine");
    return 0;
}

void btn_play_click(component* comp){
    sprite* s = (sprite*)gameObject_get_component(comp->owner, SPRITE_T);
    sprite_scale(s, -10);
    sprite_recolor(s, 150,150,150);
}

void btn_play_click_release(component* comp){
    //animate
    sprite* s = (sprite*)gameObject_get_component(comp->owner, SPRITE_T);
    sprite_scale(s, 10);
    sprite_recolor(s, 255,255,255);
    //do something
}

void btn_quit_click_release(component* comp){
    //animate
    sprite* s = (sprite*)gameObject_get_component(comp->owner, SPRITE_T);
    sprite_scale(s, 10);
    sprite_recolor(s, 255,255,255);
    //do something
    comp->owner->__scene->__game->running = false;
}

void btn_play_enter(component* comp){
    sprite* s = (sprite*)gameObject_get_component(comp->owner, SPRITE_T);
    sprite_scale(s, 5);
}
void btn_play_exit(component* comp){
    sprite* s = (sprite*)gameObject_get_component(comp->owner, SPRITE_T);
    sprite_scale(s, -5);
}

void initMainMenu(game* game){
    //create main menu bg
    gameObject* go = gameObject_new(game->current_scene);
    sprite_new(go, "resources/assets/ui/Title.png", 0, 0, 0);
    //play BTN
    go = gameObject_new(game->current_scene);
    sprite_new(go, "resources/assets/ui/start.png", 0, 150, 75);
    transform* t = gameObject_get_component(go, TRANSFORM_T);
    t->pos.x = 320;
    t->pos.y = 230;
    //btncomp
    button_new(go, btn_play_click, btn_play_click_release, btn_play_enter, btn_play_exit);

    //quit BTN
    go = gameObject_new(game->current_scene);
    sprite_new(go, "resources/assets/ui/start.png", 0, 150, 75);
    t = gameObject_get_component(go, TRANSFORM_T);
    t->pos.x = 320;
    t->pos.y = 330;
    //btncomp
    button_new(go, btn_play_click, btn_quit_click_release, btn_play_enter, btn_play_exit);

    //create ostObj
    go = gameObject_new(game->current_scene);
    audio_emitter_new(go, "resources/assets/audio/background.mp3", 1, MP3);
    dont_destroy_on_load(go); //avoid destroying this obj since it reproduce the main ost
    game->current_scene->started = true;

    //when i've added all the sprites order them by z-index 
    //vector_quick(game->current_scene->draw_mgr->drawables, z_buffer); //TODO: this throws a stack-overflow ex :c 
}

void gameLoop(game* game){

    scene* menu = scene_new(game, initMainMenu);
    menu->index = 0; //main menu
    vector_add(game->scenes, menu);
    game->current_scene = menu;

    //TEST PLAYER
    // gameObject* player = gameObject_new(game->current_scene);
    // component* c = gameObject_create_component(player);
    // //sprite_new(c, "resources/assets/player/myplane_strip3.png", 0, 0);
    // sprite_new_animated(c, "resources/assets/player/myplane_strip3.png", 1, 3, 0.1f);
    // c = gameObject_create_component(player);
    // player_new(c, 200, 2, 4);
    // vector_add(game->current_scene->gameObjects, player);

    while(game->running){
        if(game->current_scene->started == false){
            game->current_scene->init(game);
        }
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch (event.type)
            {
                case SDL_QUIT:
                    game->running = false;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        game->mouseState = 1;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.button == SDL_BUTTON_LEFT){
                        game->mouseState = 0;
                    }
                break;
                default:
                    break;
            }
        }
        tick(game);
        clear(game);
        update(game);
        draw(game);
    }

    SDL_DestroyWindow(game->__window);
    SDL_DestroyRenderer(game->__renderer);
    SDL_Quit();
}

void tick(game* game){
    game->__last_count = game->__curr_count;
    game->__curr_count = (int)SDL_GetPerformanceCounter();
    game->__frequency = (int)SDL_GetPerformanceFrequency();
    float dt = ((float)(game->__curr_count - game->__last_count) / (float)game->__frequency);
    // int fps = (int)(1.f / delta_time);
    game->delta_time = dt;
}

void clear(game* game){
    SDL_SetRenderDrawColor(game->__renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->__renderer);
}

void update(game* game){
    scene_update(game->current_scene);
}

void draw(game* game){
    scene_draw(game->current_scene);
    SDL_RenderPresent(game->__renderer);
}
