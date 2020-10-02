#pragma once
#include "Enemy.h"

class Eyeball : public Enemy {
public:
	Eyeball(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Eyeball();
};