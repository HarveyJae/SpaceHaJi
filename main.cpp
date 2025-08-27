#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

int main(int, char const **)
{
    int retval = 0;
    std::cout << "Hello,SpaceShoot." << std::endl;

    retval = SDL_Init(SDL_INIT_EVERYTHING);
    if (retval != 0)
    {
        std::cout << "SDL Init failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SpaceShoot", 200, 200, 500, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "SDL Window create failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "SDL Renderer create failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    while (SDL_TRUE)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event) == SDL_TRUE)
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Rect rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
