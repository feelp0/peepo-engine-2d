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
    g->next_scene = NULL;
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
    
    SDL_SetWindowTitle(game->__window, "peepo-engine-2d");
    return 0;
}

void init_test_scene(game* game){
    //
    gameObject* go = gameObject_new(game->current_scene, "BG-TEST");
    sprite_new(go, "resources/assets/ui/Title.png", 0, 0, 0);
    //sprite_new_animated(go, path, z_index, n_frames, animation_speed); animated sprite (TODO: add columns Y)

    //CREATE BUTTON_OBJ
    // go = gameObject_new(game->current_scene, "playBTN");
    //sprite_new(go, filePath, z_index, width, height); //if width || height are set to 0 the file size  will be used to avoid stretches
    // vec2 pos = vec2_new(320, 230);
    // go->transform->pos = pos;
    //ui_element_new(go, btn_play_click, btn_play_click_release, btn_play_enter, btn_play_exit); //implement the function obv

    //CREATE AUDIO GAME_OBJ
    // go = gameObject_new(game->current_scene, "audioEmitter");
    // audio_emitter_new(go, filePath, 1, MP3);
    // dont_destroy_on_load(go); //avoid destroying this obj since it reproduce the main ost
    
    
    game->current_scene->started = true; //MUST SET THIS TO TRUE IN A SCENE INIT

    //when i've added all the sprites order them by z-index 
    //vector_quick(game->current_scene->draw_mgr->drawables, z_buffer); //TODO: this throws a stack-overflow ex :c 
}

void update_events(game* game, SDL_Event* event){
    while(SDL_PollEvent(event)){
            switch (event->type)
            {
                case SDL_QUIT:
                    game->running = false;
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event->button.button == SDL_BUTTON_LEFT){
                        game->mouseState = 1;
                    }
                break;
                case SDL_MOUSEBUTTONUP:
                    if(event->button.button == SDL_BUTTON_LEFT){
                        game->mouseState = 0;
                    }
                break;
                default:
                    break;
            }
        }
}

void gameLoop(game* game){

    scene* menu = scene_new(game, "test-scene", init_test_scene);

    scene_set_active(menu); //set active scene

    SDL_Event event;
    while(game->running){
        //if scene is going to chage
        if(game->current_scene != game->next_scene){
            scene_change(game->current_scene, game->next_scene);
        }
        //if the scene changed but isn't initialized
        if(game->current_scene->started == false){
            game->current_scene->init(game);
            //here we could call all the component gameObjs init methods
        }

        update_events(game, &event);
        
        tick(game);
        clear(game);
        update(game);
        draw(game);
        //ACTIVATE TO DEBUG FPS (to-fix)
        // int fps = getFPS(game);
        // char title[100];
        // sprintf_s(title, sizeof(title), "PeepoEngine2D - Fps: %d", fps);
        // SDL_SetWindowTitle(game->__window, title);
    }

    //free
    scene_destroy(game->current_scene);
    SDL_DestroyWindow(game->__window);
    SDL_DestroyRenderer(game->__renderer);
    IMG_Quit();
    SDL_Quit();
}

void tick(game* game){
    game->__last_count = game->__curr_count;
    game->__curr_count = (int)SDL_GetPerformanceCounter();
    game->__frequency = (double)SDL_GetPerformanceFrequency();
    double dt = (double)((game->__curr_count - game->__last_count) * 1000 / game->__frequency);
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


int getFPS(game* game){
        game->__last_count = game->__curr_count;
        game->__curr_count = SDL_GetPerformanceCounter();
        int freq = SDL_GetPerformanceFrequency();
        float delta_time = ((float)(game->__curr_count - game->__last_count) / (float)freq);
        int fps = (int)(1.f / delta_time);
        return fps;
}
