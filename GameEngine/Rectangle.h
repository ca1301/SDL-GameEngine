#pragma once
#include "GameObject.h"
class Rectangle : GameObject
{
public:
	Rectangle(Uint8 r, Uint8 g, Uint8 b, SDL_Rect rect);
	~Rectangle();
	void Drawing();
private:
	SDL_Color rectColour;
	SDL_Rect rect;
};

