#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class LoadSDL
{
public:
	void Load();
	void Clean();
	static SDL_Renderer* m_Renderer;
protected:
	
private:
	SDL_Window* sdlWindow;
	
};

