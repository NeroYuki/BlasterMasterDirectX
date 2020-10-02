#pragma once
#include "Enemy.h"

class Skull : public Enemy {
public:
	Skull(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Skull();
};