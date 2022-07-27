#include "GameObject.h"
#include <SDL_image.h>


void GameObject::Draw(int m_frame, const char* path, float posX, float posY, float scaleX, float scaleY)
{
	m_Surface = IMG_Load(path);
	SDL_SetColorKey(m_Surface, SDL_TRUE, SDL_MapRGB(m_Surface->format, 0xFF, 0, 0xFF));
	m_frames = m_frame;
	position.x = posX;
	position.y = posY;
	if (m_Surface != nullptr)
	{
		std::cout << "Load Surface - success" << std::endl;
	}

	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
	if (m_Texture != nullptr)
	{
		std::cout << "Load Texture - success" << std::endl;
	}





	//Set the source rectangle
	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 0;
	m_sourceRectangle.w = m_Surface->w / m_frame;
	m_sourceRectangle.h = m_Surface->h;


	//Set dest rectangle
	m_destRectangle.x = position.x;
	m_destRectangle.y = position.y;
	m_destRectangle.w = m_sourceRectangle.w * scaleX;
	m_destRectangle.h = m_Surface->h * scaleY;

	//Free memory
	SDL_FreeSurface(m_Surface);
}

void GameObject::Render(int angle, SDL_RendererFlip flipped)
{
	//Copy to render window
	SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle, &m_destRectangle, angle, NULL, flipped);
}

void GameObject::Update(int m_Speed)
{
	m_destRectangle.x = position.x;
	m_destRectangle.y = position.y;
}

