#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
public:
	void Draw(int m_frame, const char* path, float posX, float posY, float scaleX, float scaleY);
	void Render();
	void Update(float dt);
	SDL_Rect GetBulletRect();
	void Destroy();
protected:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	int m_frames;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;
	Vector2 position;
	float speed = 10;
}; 
