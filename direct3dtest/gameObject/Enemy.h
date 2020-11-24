#pragma once
#include "GameObject.h"
#include "Player.h"
#define WALKING_SPEED 0.03

class Enemy : public GameObject {
protected:
	int HitPoint;
public:
	Enemy(float x, float y, int hp);
	virtual void render() = 0;
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right) = 0;
	~Enemy();
};