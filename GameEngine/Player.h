#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "SDL_image.h"
#include "Rectangle.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	//Initialise the player with a movement speed
	Player(int speed);
	//Draw the player with the amount of frames and scale needed
	void Draw(int m_frame, const char* path, float scaleX, float scaleY);
	//Render the player each frame
	void Render();
	//Get input from keyboard
	void HandleEvents();
	//Update player each frame
	void Update(float dt);
	//Determine player movement
	void HandleMovement(float dt);
	//Helper function for collision
	SDL_Rect GetPosPlayer();

	//Informs main class if player is firing
	bool playerShoot = false;
	
	int GetLives() { return lives; }
	
	int score = 0;
private:
	int movementSpeed;
	//Below used for movement
	int angle = 0;
	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;
	
	void PlayerShoot();
	//Locally keeps track of shooting
	bool shoot = false;
	int lives = 3;
};



