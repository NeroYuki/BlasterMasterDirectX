#pragma once
#include "Enemy.h"

#define BBOX_MINE_WIDTH 16
#define BBOX_MINE_HEIGHT 6

class Mine : public Enemy {
private:
	int explo = 0;
public:
	Mine(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Mine();
};