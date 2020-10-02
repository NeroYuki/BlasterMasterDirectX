#pragma once
#include "Enemy.h"

class Player : public GameObject {
public:
	Player(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Player();
};