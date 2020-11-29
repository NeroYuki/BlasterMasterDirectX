#pragma once
#include "Enemy.h"

#define BBOX_JUMPER_WIDTH 18
#define BBOX_JUMPER_HEIGHT 26

class Jumper : public Enemy {
private: 
	bool isJump = true;
	GameTimer* waitTime ;
	GameTimer* watTime2;
	int facing = 1;
	int jumpCounter = 4;
	int facing2 = 1;
public:
	Jumper(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~Jumper();
};