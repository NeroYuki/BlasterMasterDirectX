#pragma once
#include "Enemy.h"

class Dome : public Enemy {
public:
	Dome(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Dome();
};