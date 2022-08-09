#pragma once
#include "LoadSDL.h"
#include "Vector2.h"
class GameObject : public LoadSDL
{
public:

	void Draw(int m_frame, const char* path, float posX, float posY, float scaleX, float scaleY);
	void Render(int angle, SDL_RendererFlip flipped);
	void Update();
protected:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	int m_frames;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;
	Vector2 position;
};

