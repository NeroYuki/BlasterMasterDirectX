#pragma once
#include "Enemy.h"

class Orb : public Enemy {
public:
	Orb(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Orb();
};