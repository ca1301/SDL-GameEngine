#include "Start.h"


Start::Start()
{
	gameStarted = false;
}

void Start::Draw(const char* path, float posX, float posY, float scaleX, float scaleY)
{
	m_Surface = IMG_Load(path);
	SDL_SetColorKey(m_Surface, SDL_TRUE, SDL_MapRGB(m_Surface->format, 0xFF, 0, 0xFF));
	positionX = posX;
	positionY = posY;
	if (m_Surface != nullptr)
	{
		std::cout << "Load Surface - success" << std::endl;
	}

	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
	if (m_Texture != nullptr)
	{
		std::cout << "Load Texture - success" << std::endl;
	}



	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 255);

	SDL_RenderClear(m_Renderer);




	//Set the source rectangle
	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 0;
	m_sourceRectangle.w = m_Surface->w;
	m_sourceRectangle.h = m_Surface->h;


	//Set dest rectangle
	m_destRectangle.x = positionX;
	m_destRectangle.y = positionY;
	m_destRectangle.w = m_sourceRectangle.w * scaleX;
	m_destRectangle.h = m_Surface->h * scaleY;

	//Free memory
	SDL_FreeSurface(m_Surface);
}

void Start::Render()
{
	//Copy to render window
	SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle, &m_destRectangle, 0, 0, SDL_RendererFlip::SDL_FLIP_NONE);


	//Draw in window
	SDL_RenderPresent(m_Renderer);

}

void Start::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				return;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				gameStarted = true;
			}
		
		}
	}
}


