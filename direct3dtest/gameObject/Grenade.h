#pragma once
class BulletManager;
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "Enemy.h"
class Grenade : public Bullet {
protected:
	int HitPoint;
	int active = 1;
	int bullettype = 1;
	GameTimer* surviveTime;
	GameTimer* exploTime;
	int bulletheight = 28, bulletwidth = 8;
public:
	Grenade(float x, float y, float vx, float vy);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	int checkIfHit(float a, float b, float c, float d);
	~Grenade();
};