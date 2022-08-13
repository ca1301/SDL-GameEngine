#include "Bullet.h"
#include <SDL_image.h>
Bullet::Bullet()
{
	destroyed = false;
}
void Bullet::Draw(const char* path, float posX, float posY, float scaleX, float scaleY)
{
	m_Surface = IMG_Load(path);
	SDL_SetColorKey(m_Surface, SDL_TRUE, SDL_MapRGB(m_Surface->format, 0xFF, 0, 0xFF));
	position.x = posX;
	position.y = posY;
	if (m_Surface == nullptr)
	{
		std::cout << "Load Surface - failed" << std::endl;
	}

	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
	if (m_Texture == nullptr)
	{
		std::cout << "Load Texture - failed" << std::endl;
	}








	//Set the source rectangle
	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 0;
	m_sourceRectangle.w = m_Surface->w;
	m_sourceRectangle.h = m_Surface->h;


	//Set dest rectangle
	m_destRectangle.x = position.x;
	m_destRectangle.y = position.y;
	m_destRectangle.w = m_sourceRectangle.w * scaleX;
	m_destRectangle.h = m_Surface->h * scaleY;

}

void Bullet::Render()
{
	//Copy to render window
	SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle, &m_destRectangle, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}

void Bullet::Update(float dt)
{
	position.y -= dt + speed;
	m_destRectangle.y = position.y;
}

SDL_Rect Bullet::GetBulletRect()
{
	return m_destRectangle;
}

void Bullet::Destroy()
{
	SDL_DestroyTexture(m_Texture);
}
