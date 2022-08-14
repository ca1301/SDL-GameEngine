#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	
	Bullet(int direction);
	//Initial draw call for bullet
	void Draw(const char* path, float posX, float posY, float scaleX, float scaleY);
	//Render bullet on screen
	void Render();
	//Update at fixed rate
	void Update(float dt);
	//Helper function for collision
	SDL_Rect GetBulletRect();
	//Destroy bullet on collision
	void Destroy();
	//Do not collide if destroyed
	bool destroyed;

protected:
	int direction = 0;
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;
	Vector2 position;
	//Movement speed
	float speed = 10;
}; 
