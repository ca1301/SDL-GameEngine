#pragma once
#include "GameObject.h"
class Ship : public GameObject
{
public:
	bool Collision(SDL_Rect bullet);
	void Destroy();
};

