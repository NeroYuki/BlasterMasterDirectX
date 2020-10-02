#pragma once
#include "Enemy.h"

class Boss : public Enemy {
public:
	Boss(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Boss();
};