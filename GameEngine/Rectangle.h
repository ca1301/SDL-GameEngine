#pragma once
#include "LoadSDL.h"
class Rectangle : LoadSDL
{
public:
	Rectangle(Uint8 r, Uint8 g, Uint8 b);
	~Rectangle();
	void Drawing(SDL_Rect);
private:
	SDL_Color rectColour;
};

