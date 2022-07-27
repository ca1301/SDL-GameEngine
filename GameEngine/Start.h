#pragma once
#include "LoadSDL.h"
#include "SDL_image.h"
class Start : public LoadSDL
{
public:
	Start();
	void Draw(const char* path, float posX, float posY, float scaleX, float scaleY);
	void Render();
	float positionX;
	float positionY;
	void HandleEvents();
	bool gameStarted;
protected:
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destRectangle;
};

