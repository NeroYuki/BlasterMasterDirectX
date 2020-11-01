#pragma once
#include "Enemy.h"

#define BBOX_WORM_WIDTH 22
#define BBOX_WORM_HEIGHT 10

class Worm : public Enemy {
public:
	Worm(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Worm();
};