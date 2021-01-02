#include "gameObject.h"
#include "components.h"

game* game_new(int width, int height){
    game* g = malloc(sizeof(game));
    g->width = width;
    g->height = height;
    g->gameObjects = vector_new();
    g->running = true;
    g->__curr_count = (int)SDL_GetPerformanceCounter();
    g->__last_count = g->__curr_count;
    init(g);
    return g;
}

void add_gameObject(game* game, gameObject* go){
    vector_add(game->gameObjects, go);
}

int init(game* game){
    SDL_Init(SDL_INIT_VIDEO);

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

void gameLoop(game* game){

    //TEST PLAYER
    gameObject* player = gameObject_new(game);
    component* c = gameObject_create_component(player);
    //sprite_new(c, "resources/assets/player/myplane_strip3.png", 0, 0);
    sprite_new_animated(c, "resources/assets/player/myplane_strip3.png", 3, 0.1f);
    c = gameObject_create_component(player);
    player_new(c, 200, 2, 4);
    vector_add(game->gameObjects, player);

    while(game->running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                game->running = false;
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
    for (uint i = 0; i < vector_size(game->gameObjects); i++)
    {
        gameObject* go = vector_at(game->gameObjects, i);
        gameObject_update(go);
    }
    
}

void draw(game* game){
    SDL_RenderPresent(game->__renderer);
}
