#pragma once
#include "Enemy.h"

class Mine : public Enemy {
public:
	Mine(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Mine();
};