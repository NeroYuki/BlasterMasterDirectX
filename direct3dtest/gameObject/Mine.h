#pragma once
#include "Enemy.h"

#define BBOX_MINE_WIDTH 16
#define BBOX_MINE_HEIGHT 6

class Mine : public Enemy {
public:
	Mine(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Mine();
};