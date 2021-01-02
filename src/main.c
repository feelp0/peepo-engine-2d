#define SDL_MAIN_HANDLED
#include "game.h"

int main() {   
    game* game = game_new(640, 480); 
    gameLoop(game);
    return 0;
}