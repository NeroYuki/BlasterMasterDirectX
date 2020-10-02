#pragma once
#include "Enemy.h"

class Insect : public Enemy {
public:
	Insect(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Insect();
};