#pragma once
#include "Enemy.h"

#define BBOX_SKULL_WIDTH 18
#define BBOX_SKULL_HEIGHT 21

class Skull : public Enemy {
private:
	int skullstate = 1;
	GameTimer* skulltimer1;
	GameTimer* skulltimer2;
	int facing = -1;
public:
	Skull(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Skull();
};