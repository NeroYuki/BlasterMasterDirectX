#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
protected:
	int HitPoint;
public:
	Enemy(float x, float y, int hp);
	virtual void render() = 0;
	virtual void update(DWORD dt) = 0;
	~Enemy();
};