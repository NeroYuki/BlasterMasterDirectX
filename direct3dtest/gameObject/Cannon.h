#pragma once
#include "Enemy.h"

#define BBOX_CANNON_WIDTH 26
#define BBOX_CANNON_HEIGHT 26

class Cannon : public Enemy {
public:
	Cannon(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Cannon();

};