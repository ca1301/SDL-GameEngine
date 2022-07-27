#include "Player.h"





Player::Player(int speed)
{
	movementSpeed = speed;

	//Player Border
	playerRect = new Rectangle(255, 255, 255);
}

void Player::Draw(int m_frame, const char* path, float scaleX, float scaleY)
{
	m_Surface = IMG_Load(path);
	SDL_SetColorKey(m_Surface, SDL_TRUE, SDL_MapRGB(m_Surface->format, 0xFF, 0, 0xFF));
	m_frames = m_frame;
	position.x = 580;
	position.y = 877;
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





	//Set the source rectangle
	m_sourceRectangle.x = 0;
	m_sourceRectangle.y = 0;
	m_sourceRectangle.w = m_Surface->w / m_frame;
	m_sourceRectangle.h = m_Surface->h;


	//Set dest rectangle

	m_destRectangle.w = m_sourceRectangle.w * scaleX;
	m_destRectangle.h = m_Surface->h * scaleY;

	//Free memory
	//SDL_FreeSurface(m_Surface);
}


void Player::Render()
{
	//Copy to render window
	SDL_RenderCopyEx(m_Renderer, m_Texture, &m_sourceRectangle, &m_destRectangle, 0, NULL, SDL_FLIP_NONE);
	
}

void Player::Update(float dt)
{
	HandleMovement(dt);

	m_sourceRectangle.x = m_sourceRectangle.w * ((SDL_GetTicks() / 150) % m_frames);


	m_destRectangle.x = position.x;
	m_destRectangle.y = position.y;


}

void Player::HandleMovement(float dt)
{
	if (left == 1 && right == 0 && m_destRectangle.x > 5)
	{
		position.x -= movementSpeed + dt;
	}
	if (left == 0 && right == 1 && m_destRectangle.x < (1280 - m_destRectangle.w))
	{
		position.x += movementSpeed + dt;
	}
}

SDL_Rect Player::GetPosPlayer()
{
	SDL_Rect m_player = m_destRectangle;


	if (angle != 0)
	{
		m_player.x += (m_player.w - m_player.h) / 2;
		m_player.y -= (m_player.w - m_player.h) / 2;

		int temp = m_player.w;
		m_player.w = m_player.h;
		m_player.h = temp;
	}

	return m_player;
}


void Player::PlayerShoot()
{
	playerShoot = true;
}






void Player::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				left = 1;
			}
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
				right = 1;
			}
			if (event.key.keysym.sym == SDLK_SPACE && shoot == false)
			{
				PlayerShoot();
				shoot = true;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				left = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT)
			{
				right = 0;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				shoot = false;
				playerShoot = false;
			}
		}
	}
}
