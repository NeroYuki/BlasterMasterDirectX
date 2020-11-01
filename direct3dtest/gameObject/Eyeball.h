#pragma once
#include "Enemy.h"

#define BBOX_EYEBALL_WIDTH 16
#define BBOX_EYEBALL_HEIGHT 16

class Eyeball : public Enemy {
public:
	Eyeball(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Eyeball();
};