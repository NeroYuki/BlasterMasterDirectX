#pragma once
#include "Enemy.h"

#define BBOX_INSECT_WIDTH 20
#define BBOX_INSECT_HEIGHT 20

class Insect : public Enemy {
public:
	Insect(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Insect();
};