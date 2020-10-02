#pragma once
#include "Enemy.h"

class Teleporter : public Enemy {
public:
	Teleporter(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Teleporter();
};