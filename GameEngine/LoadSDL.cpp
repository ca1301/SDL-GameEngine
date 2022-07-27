#include "LoadSDL.h"

SDL_Renderer* LoadSDL::m_Renderer = nullptr;


void LoadSDL::Load()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialize SDL - success" << std::endl;
        //Renderering window
        sdlWindow = SDL_CreateWindow("Space Invaded", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 940, SDL_WINDOW_SHOWN);

        m_Renderer = SDL_CreateRenderer(sdlWindow, 0, -1);
        if (m_Renderer != nullptr)
        {
            std::cout << "Create Renderer - success" << std::endl;
        }
        else
        {
            std::cout << "Create Renderer - failed" << std::endl;
        }
        if (TTF_Init() == -1)
        {
            std::cout << "Failed to initialize TTF" << std::endl;
        }
    }
    else
    {
        std::cout << "Initialize SDL - failed" << std::endl;
    }

}

void LoadSDL::Clean()
{
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyRenderer(m_Renderer);
    SDL_Quit();
}




