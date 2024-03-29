#pragma once
#include "Enemy.h"

#define BBOX_BOSS_WIDTH 1
#define BBOX_BOSS_HEIGHT 1

class Boss : public Enemy {
private:
	GameTimer* shootInterval;
	int waiting;
	int yLevel;
public:
	Boss(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	void getLeftHand(float&x,float&y);
	void getRightHand(float& x, float& y);
	void setisdie() { this->isDie = 1; };
	~Boss();
};