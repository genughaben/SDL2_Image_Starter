#include "Game.h"
#include <iostream>
#include "SDL_image.h"

Game *game = nullptr;

int main(int argc, char* args[]) {


    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("THE_GAME_TITLE",
               SDL_WINDOWPOS_CENTERED,
               SDL_WINDOWPOS_CENTERED,
               800,
               600,
               false
    );

    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();

    return 0;
}