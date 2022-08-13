#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class LoadSDL
{
public:
	//Initialise SDL
	void Load();
	//Clean up SDL before closing the application
	void Clean();
	//Static reference to the renderer
	static SDL_Renderer* m_Renderer;
protected:
	
private:
	//Pointer to the window
	SDL_Window* sdlWindow;
	
};

