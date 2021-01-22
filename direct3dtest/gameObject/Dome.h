#pragma once
#include "Enemy.h"

#define BBOX_DOME_WIDTH 12
#define BBOX_DOME_HEIGHT 12
//currently based on sprite, may change

class Dome : public Enemy {
private:
	int domestate = 0;
	bool isonwall = false;
	int godown = 0;
	int goup = 0;
	int goright = 0;
	int goleft = 0;
	int onrightwall = 0;
	int onleftwall = 0;
	int ontopwall = 0;
	int onbtottomwall = 0;
	int nx1 = 0;
	int ny1 = 0;
	int nx2 = 0;
	int ny2 = 0;
	float velx = 32.00, vely = 32.00;
public:
	Dome(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Dome();
	void checkdirection();
};