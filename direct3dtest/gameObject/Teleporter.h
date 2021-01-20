#pragma once
#include "Enemy.h"
#include "../SharedData.h"

#define BBOX_TELEPORTER_WIDTH 24
#define BBOX_TELEPORTER_HEIGHT 32

class Teleporter : public Enemy {
	GameTimer* moveInterval;
	GameTimer* stopInterval;
	int stopinterval;
	float velocity = 0;
	int direction=1;
	int numberOfTeleportation;
public:
	Teleporter(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Teleporter();
};