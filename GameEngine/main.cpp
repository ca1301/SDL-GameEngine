#include <iostream>
#include "LoadSDL.h"
#include "Player.h"
#include "TextScreen.h"
#include "Start.h"
#include "Ship.h"
#include <vector>
#include <SDL_mixer.h>
#include "Sound.h"
#include <algorithm>

using namespace std;
//List to store the enemy bullets active in the scene
vector <Bullet*> enemyBullets;
//List to store the alive enemy ships
vector <Ship*> aliveShips;
float gameTime = 0;
float fireRate = 0.2f;
float lastBullet = 0;

bool CheckRoundOver(vector<Ship*> ships)
{
	
	int aliveEnemies = 0;
	for (size_t i = 0; i < ships.size(); i++)
	{
		if (!ships[i]->destroyed)
		{
			aliveEnemies++;
		}
	}
	//If the alive enemies count equals 0 then the game is over
	if (aliveEnemies == 0)
	{
		return true;
	}
	return false;
}


void Collide(Ship* ship, Bullet* bullet, Player* player, Sound* destroySound)
{
	if ((bullet->GetBulletRect().x - ship->GetShipRect().x < ship->GetShipRect().w) &&
		(ship->GetShipRect().x - bullet->GetBulletRect().x < bullet->GetBulletRect().w) &&
		(bullet->GetBulletRect().y - ship->GetShipRect().y < ship->GetShipRect().h) &&
		(ship->GetShipRect().y - bullet->GetBulletRect().y < bullet->GetBulletRect().h))
	{
		bullet->destroyed = true;
		bullet->Destroy();
		ship->destroyed = true;
		ship->Destroy();
		player->score += 30;
		if (Mix_PlayChannel(-1, destroySound->wave(), 0, ) == -1)
		{
			cout << "Failed to play sound" << endl;
		}
	}
	return;
}

//Check if bullet hit player
bool PlayerCollide(Bullet* bullet, Player* player)
{
	if ((bullet->GetBulletRect().x - player->GetPosPlayer().x < player->GetPosPlayer().w) &&
		(player->GetPosPlayer().x - bullet->GetBulletRect().x < bullet->GetBulletRect().w) &&
		(bullet->GetBulletRect().y - player->GetPosPlayer().y < player->GetPosPlayer().h) &&
		(player->GetPosPlayer().y - bullet->GetBulletRect().y < bullet->GetBulletRect().h))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Handle enemies shooting at player
void EnemyShoot(vector <Ship*> ships, float dt)
{
	//Increase the game time for timing the shots
	gameTime += dt;


	//Reset the list of alive ships
	aliveShips.clear();
	for (size_t i = 0; i < ships.size(); i++)
	{
		if (ships[i]->destroyed == false)
		{
			//Add the current alive ships into list
			aliveShips.push_back(ships[i]);
		}
	}
	//check if time is greater than firerate
	if (gameTime > fireRate + lastBullet)
	{
		lastBullet = gameTime + fireRate;
		if (aliveShips.size() > 0)
		{
			//Pick a random ship out of the alive ones to shoot
			int randomShip = rand() % aliveShips.size();
			//Create a bullet at the random ships position
			Bullet* bullet = new Bullet(1);
			bullet->Draw("../assets/player/Bullet.png", aliveShips[randomShip]->GetShipRect().x, aliveShips[randomShip]->GetShipRect().y - 30, 2, 2);
			enemyBullets.push_back(bullet);
		}
	}
}




int main(int argc, char** argv)
{
	//Initialise objects
	LoadSDL* loadSDL = new LoadSDL();
	Start* startScreen = new Start();
	int lastUpdate = 0;
	GameObject* background = new GameObject();
	//Scene management
	int playerLives = 1;
	vector <Bullet*> bullets;
	vector <Ship*> ships;
	bool playerDied = false;
	bool gameWon = false;
	srand(time(0));

	//Enemies
	int columns = 15;
	int rows = 3;
	bool movingRight = true;
	bool movingDown = false;
	int amountToMoveDown = 60;
	int targetYPosition = 0;

	

	//Initialize player with a movement speed of 5
	Player* player = new Player(5);

	//UI
	TextScreen* scoreText = new TextScreen();
	SDL_Color scoreTextColour = { 0,0,200,0 };
	scoreText->Draw(20, "../assets/Roboto.ttf", 40, 900, scoreTextColour);

	TextScreen* playerLivesText = new TextScreen();
	SDL_Color roundTextColour = { 0,0,200,0 };
	playerLivesText->Draw(20, "../assets/Roboto.ttf", 1150, 900, roundTextColour);



	loadSDL->Load();
	//Configure the Start Screen, Player and Backgroud
	startScreen->Draw("../assets/start_screen.png", 0, 0, 1, 1);
	player->Draw(1, "../assets/player/Ship.png", 3, 3);
	background->Draw(1, "../assets/background.png", 0, 0, 1, 1);

	//Sounds initialization
	Sound* sound = new Sound("../assets/shoot_sound.wav");
	Sound* explosionSound = new Sound("../assets/ship_destroy.wav");


	//Initialize enemies
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (i == 0)
			{
				Ship* ship = new Ship();
				ship->Draw(1, "../assets/player/Enemy_3.png", 15 + 60 * j, 40 + 60 * i, 2, 2);
				ships.push_back(ship);
			}
			else if (i == 1)
			{
				Ship* ship = new Ship();
				ship->Draw(1, "../assets/player/Enemy_2.png", 15 + 60 * j, 40 + 60 * i, 2, 2);
				ships.push_back(ship);
			}
			else
			{
				Ship* ship = new Ship();
				ship->Draw(1, "../assets/player/Enemy_1.png", 15 + 60 * j, 40 + 60 * i, 2, 2);
				ships.push_back(ship);
			}
					

		}
	}


	//Show game menu before starting game
	while (startScreen->gameStarted == false)
	{
		startScreen->Render();
		startScreen->HandleEvents();
	}




	//Game Loop
	while (playerDied == false && gameWon == false)
	{
		//Clear the screen each frame
		SDL_RenderClear(loadSDL->m_Renderer);

		background->Render(0, SDL_RendererFlip::SDL_FLIP_NONE);

		//Get delta time for player/enemy movement
		unsigned int ticks = SDL_GetTicks() - lastUpdate;
		float deltaTime = ticks / 1000.0f;
		lastUpdate = SDL_GetTicks();

		

		//Rendering and update the score text to display the players current score
		scoreText->Update("Score:  " + std::to_string(player->score));
		scoreText->Render();

		//Rendering and update the round text to display the players current round
		playerLivesText->Update("Lives:  " + std::to_string(playerLives));
		playerLivesText->Render();

		//Triggered from the player script
		if (player->playerShoot == true)
		{
			player->playerShoot = false;
			Bullet* bullet = new Bullet(0);
			bullet->Draw("../assets/player/Bullet.png", player->GetPosPlayer().x - 7, player->GetPosPlayer().y - 35, 2, 2);
			bullets.push_back(bullet);

			if (Mix_PlayChannel(-1, sound->wave(), 0, ) == -1)
			{
				cout << "Failed to play sound" << endl;
			}
		}

		//Loop through the bullets and update them
		for (int i = 0; i < bullets.size(); i++) {

			bullets[i]->Update(deltaTime);
			bullets[i]->Render();

			//If the bullet gets to the top of the page without hitting anything we need to destroy it
			if (bullets[i]->GetBulletRect().y < 0)
			{
				bullets[i]->Destroy();
				bullets.erase(bullets.begin() + i);
			}
		}

		for (int i = 0; i < enemyBullets.size(); i++) {

			enemyBullets[i]->Update(deltaTime);
			enemyBullets[i]->Render();

			if (PlayerCollide(enemyBullets[i], player))
			{
				playerDied = true;
			}
		}
		//Loop through the ships and update them
		for (int i = 0; i < ships.size(); i++) {
			ships[i]->Update(deltaTime);
			ships[i]->Render(0, SDL_RendererFlip::SDL_FLIP_NONE);


			
			//Handle enemy movement to the right
			if (ships[0]->GetShipRect().x < 400 && movingRight && !movingDown)
			{
				float x = ships[i]->GetShipRect().x;
				ships[i]->Move(x += 1, ships[i]->GetShipRect().y);
			}
			else if (ships[0]->GetShipRect().x >= 400 && movingRight)
			{
				movingRight = false;
				movingDown = true;
				targetYPosition = ships[0]->GetShipRect().y + amountToMoveDown;
			}


			//Handle enemy movement to the left
			if (ships[0]->GetShipRect().x > 15 && !movingRight && !movingDown)
			{
				float x = ships[i]->GetShipRect().x;
				ships[i]->Move(x -= 1, ships[i]->GetShipRect().y);
			}
			else if (ships[0]->GetShipRect().x <= 15 && !movingRight && !movingDown)
			{
				movingRight = true;
				movingDown = true;
				targetYPosition = ships[0]->GetShipRect().y + amountToMoveDown;
			}

			//Handle enemies moving down
			if (ships[0]->GetShipRect().y < targetYPosition && movingDown)
			{
				float y = ships[i]->GetShipRect().y;
				ships[i]->Move(ships[i]->GetShipRect().x, y += 1);
			}
			else if (ships[0]->GetShipRect().y >= targetYPosition && movingDown)
			{
				movingDown = false;
			}
			
		}


		//Handle bullet and ship collision as well as check the end of the round
		for (int i = 0; i < ships.size(); i++)
		{
			for (int j = 0; j < bullets.size(); j++)
			{
				if (ships[i]->destroyed == false && bullets[j]->destroyed == false)
				{
					Collide(ships[i], bullets[j], player, explosionSound);
					if (CheckRoundOver(ships))
					{
						gameWon = true;
						for (size_t g = 0; g < ships.size(); g++)
						{
							ships.erase(ships.begin() + g);
						}
					}
				}
			}
		}
		//Enemy shoot at player
		EnemyShoot(ships, deltaTime);

		//Update the player based on keyboard input
		player->Update(deltaTime);
		player->HandleEvents();
		player->Render();

		//Draw in window
		SDL_RenderPresent(loadSDL->m_Renderer);
	}

	if (gameWon)
		std::cout << "You Won!!!" << std::endl;

	if (playerDied)
		std::cout << "You Died!" << std::endl;

	//Free up music and clean up SDL
	Mix_FreeChunk(sound->wave());
	loadSDL->Clean();
	return 0;
}





