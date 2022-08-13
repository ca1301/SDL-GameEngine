#pragma once
#include "GameObject.h"
class Ship : public GameObject
{
public:
	
	Ship();
	SDL_Rect GetShipRect() { return m_destRectangle; }
	//Destroy ship when collision is detected
	void Destroy();
	//Do not collide with anything if destroyed
	bool destroyed;
	//Handle ship movement
	void Move(float x, float y);
};

