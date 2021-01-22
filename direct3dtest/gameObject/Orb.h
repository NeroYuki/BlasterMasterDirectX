#pragma once
#include "Enemy.h"

#define BBOX_ORB_WIDTH 18
#define BBOX_ORB_HEIGHT 18

class Orb : public Enemy {
private:
	GameTimer* moveInterval;
	int stopinterval;
	int type = 0;
public:
	Orb(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Orb();
};