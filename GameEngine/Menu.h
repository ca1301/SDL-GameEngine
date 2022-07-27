#pragma once
#include <SDL.h>
#include <Windows.h>

class Menu
{
public:
	Menu();
	~Menu();
	void GetMenu();
	int DisplayDialogBox();
private:
	HWND window;
	HMENU menu;
	SDL_Window* sdlWindow2;
	SDL_Renderer* sdlRenderer2;
};

