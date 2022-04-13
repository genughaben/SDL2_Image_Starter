#include "Game.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* playerTex;
SDL_Surface *image;
SDL_RWops *readWriteOperation;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int window_flags = 0;

    // toggle fullscreen mode
    if(fullscreen)
    {
        window_flags = SDL_WINDOW_FULLSCREEN;
    }

    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        isRunning = false;
        std::cout << "Subsystems initialization failed.." << std::endl;
        return;
    }
    isRunning = true;

    //Create window
    window = Game::createSDLWindow(title, xpos, ypos, width, height, window_flags);
    // Create renderer
    renderer = Game::createSDLRenderer(window, -1, SDL_RENDERER_SOFTWARE && SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);

    //Setup and initialize SDL2_Image library with supported formats
    int imgFlags = IMG_INIT_PNG;
    int initStatus = IMG_Init(imgFlags);
    if (!(initStatus & imgFlags)) {
        printf("SDL2_Image format not available. SDL_image Error: %s\\n", IMG_GetError());
    }

    // Load example PNG image into surface
    loadAndDisplayImage("/images/mario.png");

}

void Game::loadAndDisplayImage(const char * filePath)
{
    readWriteOperation = SDL_RWFromFile(filePath, "rb");
    if(!readWriteOperation) {
    printf("Error: SDL read/write operation failed : %s\n", SDL_GetError());
    }

    // load image into surface
    image = IMG_LoadPNG_RW(readWriteOperation);
    if(!image) {
    printf("Error: Load file from read/write operation to surface failed: %s\n", IMG_GetError());
    // handle error
    }
    playerTex = SDL_CreateTextureFromSurface(renderer, image);
}

SDL_Window * Game::createSDLWindow(const char *title, int xpos, int ypos, int width, int height, Uint32 flags){
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(window)
    {
        std::cout << "Window created!" << std::endl;
    }
    return window;
}

SDL_Renderer * Game::createSDLRenderer(SDL_Window * window, int index, Uint32 flags) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE && SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC);
    if(renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        std::cout << "Renderer is created!" << std::endl;
    }
    return renderer;
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
    }
}

void Game::update(){
    // clear screen
    // do updates
}

void Game::render(){
    SDL_RenderClear(renderer);
    // here we do add stuff to render
    SDL_RenderCopy(renderer, playerTex, NULL, NULL);
    SDL_RenderPresent(renderer);

}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    // free our png surface
    SDL_FreeSurface(image);
    IMG_Quit();
    std::cout << "Game has been cleaned and closed." << std::endl;
}

bool Game::running(){
    return isRunning;
}