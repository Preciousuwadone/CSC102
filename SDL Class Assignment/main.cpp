#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void drawHouse(SDL_Renderer* renderer) {
    // Set color to brown for house body
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_Rect houseRect = { 300, 300, 200, 200 };
    SDL_RenderFillRect(renderer, &houseRect);

    // Set color to dark grey for roof
    SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);
    SDL_Point roofPoints[3] = { {250, 300}, {400, 150}, {550, 300} };
    SDL_RenderDrawLines(renderer, roofPoints, 3);

    // Set color to blue for door
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect doorRect = { 375, 400, 50, 100 };
    SDL_RenderFillRect(renderer, &doorRect);

    // Set color to white for windows
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect windowRect1 = { 325, 325, 50, 50 };
    SDL_RenderFillRect(renderer, &windowRect1);
    SDL_Rect windowRect2 = { 425, 325, 50, 50 };
    SDL_RenderFillRect(renderer, &windowRect2);
}

void drawTree(SDL_Renderer* renderer) {
    // Set color to brown for tree trunk
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    SDL_Rect trunkRect = { 350, 400, 100, 200 };
    SDL_RenderFillRect(renderer, &trunkRect);

    // Set color to green for leaves
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect leavesRect = { 250, 300, 300, 100 };
    SDL_RenderFillRect(renderer, &leavesRect);
}

void drawSun(SDL_Renderer* renderer) {
    // Set color to yellow for sun
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for (int w = 0; w < 100; w++) {
        for (int h = 0; h < 100; h++) {
            int dx = 400 - (400 - 50 + w); // horizontal offset
            int dy = 100 - (100 - 50 + h); // vertical offset
            if ((dx * dx + dy * dy) <= (50 * 50)) {
                SDL_RenderDrawPoint(renderer, 700 + dx, 100 + dy);
            }
        }
    }
}

enum Scene { HOUSE, TREE };

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Scene Switcher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    Scene currentScene = HOUSE;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_1:
                    currentScene = HOUSE;
                    break;
                case SDLK_2:
                    currentScene = TREE;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue background
        SDL_RenderClear(renderer);

        if (currentScene == HOUSE) {
            drawHouse(renderer);
        }
        else if (currentScene == TREE) {
            drawTree(renderer);
            drawSun(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
