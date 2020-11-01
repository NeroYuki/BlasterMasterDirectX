#pragma once
#include "Enemy.h"

#define BBOX_SKULL_WIDTH 18
#define BBOX_SKULL_HEIGHT 21

class Skull : public Enemy {
public:
	Skull(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Skull();
};