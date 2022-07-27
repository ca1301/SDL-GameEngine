#pragma once
#include "GameObject.h"
class AI : public GameObject
{
public:
	void SetTarget(GameObject* target);
protected:
	int health;
	int lives;
};

