#pragma once
#include "Enemy.h"
#include <math.h>
#define BBOX_BOSS_WIDTH 1
#define BBOX_BOSS_HEIGHT 1

class BossJoint : public Enemy {
private:
	GameTimer* moveInterval;
	float len;
	float angle = 0;
	float sw = 0;
public:
	float x2, y2;
	BossJoint(float x, float y,float len,float i, int hp);
	BossJoint(BossJoint* b,float len,float i);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	void update();
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~BossJoint();
	void calculateB();
	void getEnd(float& x, float& y);
	void follow(BossJoint* child);
	void follow(float tx, float ty);
	void setState(int i);
	void setisdie() { this->isDie = 1; };

};


