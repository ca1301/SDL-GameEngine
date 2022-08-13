#pragma once
#include "LoadSDL.h"
#include <SDL_ttf.h>
#include <string>

using namespace std;

class TextScreen : LoadSDL
{

public:
	void Draw(int fontSize, string fontPath, int posX, int posY, SDL_Color textColour);
	void Render();
	void Update(string str);
	void LoadFont(const char*);
private:
	string m_fontPath;
	int m_fontSize;
	int m_posX;
	int m_posY;
	TTF_Font* m_ttfFont;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
	SDL_Color textColour;
	SDL_Rect mTextRect;
};

