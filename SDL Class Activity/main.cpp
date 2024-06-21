#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 20;
const int CHANGE_DIRECTION_INTERVAL = 2000; // Change direction every 2000ms (2 seconds)

struct Ball {
    int x, y;
    int velX, velY;
    int radius;
};

void initBall(Ball& ball) {
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.velX = (rand() % 5 + 1) * (rand() % 2 == 0 ? 1 : -1); // Random velocity between -5 and 5
    ball.velY = (rand() % 5 + 1) * (rand() % 2 == 0 ? 1 : -1);
    ball.radius = BALL_RADIUS;
}

void moveBall(Ball& ball) {
    ball.x += ball.velX;
    ball.y += ball.velY;

    // Bounce off the walls
    if (ball.x - ball.radius < 0 || ball.x + ball.radius > SCREEN_WIDTH) {
        ball.velX = -ball.velX;
    }
    if (ball.y - ball.radius < 0 || ball.y + ball.radius > SCREEN_HEIGHT) {
        ball.velY = -ball.velY;
    }
}

void changeDirection(Ball& ball) {
    ball.velX = (rand() % 5 + 1) * (rand() % 2 == 0 ? 1 : -1);
    ball.velY = (rand() % 5 + 1) * (rand() % 2 == 0 ? 1 : -1);
}

void drawBall(SDL_Renderer* renderer, const Ball& ball) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for the ball
    for (int w = 0; w < ball.radius * 2; w++) {
        for (int h = 0; h < ball.radius * 2; h++) {
            int dx = ball.radius - w;
            int dy = ball.radius - h;
            if ((dx * dx + dy * dy) <= (ball.radius * ball.radius)) {
                SDL_RenderDrawPoint(renderer, ball.x + dx, ball.y + dy);
            }
        }
    }
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Moving Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    Ball ball;
    initBall(ball);

    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastDirectionChangeTime = SDL_GetTicks();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastDirectionChangeTime > CHANGE_DIRECTION_INTERVAL) {
            changeDirection(ball);
            lastDirectionChangeTime = currentTime;
        }

        moveBall(ball);

        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue background
        SDL_RenderClear(renderer);

        drawBall(renderer, ball);

        SDL_RenderPresent(renderer);

        // Cap the frame rate to 60 FPS
        Uint32 frameTime = SDL_GetTicks() - lastTime;
        if (frameTime < 1000 / 60) {
            SDL_Delay(1000 / 60 - frameTime);
        }
        lastTime = SDL_GetTicks();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
