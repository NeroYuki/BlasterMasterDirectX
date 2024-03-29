#pragma once
#include "Enemy.h"

#define BBOX_FLOATER_WIDTH 20
#define BBOX_FLOATER_HEIGHT 20

class Floater : public Enemy {
private:
	GameTimer* shoottimer;
public:
	Floater(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float &top, float &left, float &bottom, float &right);
	~Floater();
};