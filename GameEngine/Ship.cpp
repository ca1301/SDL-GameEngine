#include "Ship.h"

bool Ship::Collision(SDL_Rect bullet)
{
	if ((bullet.x - m_destRectangle.x < m_destRectangle.w) &&
		(m_destRectangle.x - bullet.x < bullet.w) &&
		(bullet.y - m_destRectangle.y < m_destRectangle.h) &&
		(m_destRectangle.y - bullet.y < bullet.h))
	{
		std::cout << "Collide" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

void Ship::Destroy()
{
	SDL_DestroyTexture(m_Texture);
}
