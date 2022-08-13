#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "SDL_image.h"
#include "Rectangle.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	Player(int speed);
	void Draw(int m_frame, const char* path, float scaleX, float scaleY);
	void Render();
	void HandleEvents();
	void Update(float dt);
	void HandleMovement(float dt);
	SDL_Rect GetPosPlayer();
	bool playerShoot = false;
	int GetLives() { return lives; }
	int score = 0;
private:
	int movementSpeed;
	int angle = 0;
	int left = 0;
	int right = 0;
	int up = 0;
	int down = 0;
	void PlayerShoot();
	bool shoot = false;
	int lives = 3;
};



