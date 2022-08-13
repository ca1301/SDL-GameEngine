#pragma once
#include "LoadSDL.h"
#include "Vector2.h"
class GameObject : public LoadSDL
{
public:
	//Initial draw
	void Draw(int m_frame, const char* path, float posX, float posY, float scaleX, float scaleY);
	//Render the GameObject at a specific angle and flipped or not
	void Render(int angle, SDL_RendererFlip flipped);
	//Update GameObject
	void Update(float dt);
protected:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	//Amount of frames for animation
	int m_frames;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;
	Vector2 position;
};

