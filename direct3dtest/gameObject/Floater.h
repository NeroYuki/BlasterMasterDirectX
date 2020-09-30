#pragma once
#include "Enemy.h"

class Floater : public Enemy {
public:
	Floater(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Floater();
};