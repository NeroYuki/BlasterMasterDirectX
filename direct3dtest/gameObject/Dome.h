#pragma once
#include "Enemy.h"

#define BBOX_DOME_WIDTH 18
#define BBOX_DOME_HEIGHT 18
//currently based on sprite, may change

class Dome : public Enemy {
public:
	Dome(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Dome();
};