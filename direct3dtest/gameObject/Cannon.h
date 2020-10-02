#pragma once
#include "Enemy.h"

class Cannon : public Enemy {
public:
	Cannon(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Cannon();

};