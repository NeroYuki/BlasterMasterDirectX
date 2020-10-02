#pragma once
#include "Enemy.h"

class Jumper : public Enemy {
public:
	Jumper(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Jumper();
};