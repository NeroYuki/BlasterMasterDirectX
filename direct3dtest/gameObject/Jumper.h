#pragma once
#include "Enemy.h"

#define BBOX_JUMPER_WIDTH 18
#define BBOX_JUMPER_HEIGHT 26

class Jumper : public Enemy {
public:
	Jumper(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Jumper();
};