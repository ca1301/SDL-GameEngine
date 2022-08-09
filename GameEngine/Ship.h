#pragma once
#include "GameObject.h"
class Ship : public GameObject
{
public:
	Ship();
	SDL_Rect GetShipRect() { return m_destRectangle; }
	void Destroy();
	bool destroyed;
	void Move(float x, float y);
};

