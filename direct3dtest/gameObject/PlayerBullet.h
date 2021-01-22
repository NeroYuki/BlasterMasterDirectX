#pragma once
class BulletManager;
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "Enemy.h"
class PLayerBullet : public Bullet {
protected:
	int HitPoint;
	int active = 1;
	int bullettype = 1;
	int bulletdirection = 0;
	GameTimer* surviveTime;
	GameTimer* exploTime;
	GameTimer* TurningTime;
	GameTimer* TurningTime2;
	int bulletheight = 28, bulletwidth = 8;
	float minenemyx = 100, minenemyy = 100;
	float velocity = 0;
	DWORD T = 0;
public:
	PLayerBullet(float x, float y, float vx, float vy, int type, int direction);
	PLayerBullet(float x, float y, float vx, float vy, int type, int direction,int value);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~PLayerBullet();
	void getDxDy(float& dx, float& dy, DWORD dt, DWORD& Totaltime);
};

