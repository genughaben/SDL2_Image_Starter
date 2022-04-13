#ifndef SDL2_IMAGE_STARTER_H
#define SDL2_IMAGE_STARTER_H

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

class Game {
public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Renderer * createSDLRenderer(SDL_Window * window, int index, Uint32 flags);
    SDL_Window * createSDLWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
    void loadAndDisplayImage(const char *filePath);
};

#endif //SDL2_IMAGE_STARTER_H
