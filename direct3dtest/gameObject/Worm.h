#pragma once
#include "Enemy.h"

class Worm : public Enemy {
public:
	Worm(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Worm();
};