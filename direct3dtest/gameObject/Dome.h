#pragma once
#include "Enemy.h"

#define BBOX_DOME_WIDTH 12
#define BBOX_DOME_HEIGHT 12
//currently based on sprite, may change

class Dome : public Enemy {
private:
	int domestate = 0;
	bool isonwall = false;
	float velx = 32.00, vely = 32.00;
public:
	Dome(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Dome();
};