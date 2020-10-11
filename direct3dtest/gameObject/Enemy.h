#pragma once
#include "GameObject.h"
#define WALKING_SPEED 0.03

class Enemy : public GameObject {
protected:
	int HitPoint;
public:
	Enemy(float x, float y, int hp);
	virtual void render() = 0;
	virtual void update(DWORD dt) = 0;
	~Enemy();
};