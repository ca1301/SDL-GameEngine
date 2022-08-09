#include "TextScreen.h"
#include <iostream>

using namespace std;


void TextScreen::Draw(int fontSize, string fontPath, int posX, int posY)
{
	m_fontPath = fontPath;
	m_fontSize = fontSize;
	m_posX = posX;
	m_posY = posY;
	//Blue Colour
	textColour = { 0, 0, 255, 255};
	mTextRect.x = m_posX;
	mTextRect.y = m_posY;
}

void TextScreen::Render()
{
	
	SDL_RenderCopy(m_Renderer, textTexture, nullptr, &mTextRect);
}

void TextScreen::Update(string str)
{
	LoadFont(str.c_str());
	SDL_QueryTexture(textTexture, nullptr, nullptr, &mTextRect.w, &mTextRect.h);

}

void TextScreen::LoadFont(const char* messageText)
{
	m_ttfFont = TTF_OpenFont(m_fontPath.c_str(), m_fontSize);
	textSurface = TTF_RenderText_Solid(m_ttfFont, messageText, textColour);
	textTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
	SDL_FreeSurface(textSurface);
}
