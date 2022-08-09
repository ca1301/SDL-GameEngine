#include "Ship.h"


Ship::Ship()
{
	destroyed = false;
}

void Ship::Destroy()
{
	SDL_DestroyTexture(m_Texture);
}

void Ship::Move(float x, float y)
{
	position.x = x;
	position.y = y;
}
