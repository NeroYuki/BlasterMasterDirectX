#pragma once
class BulletManager;
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "Enemy.h"
class PLayerBullet : public Bullet {
protected:
	int HitPoint;
	int active=1;
	GameTimer* surviveTime;
	GameTimer* exploTime;
	int bulletheight=28, bulletwidth=8;
public:
	PLayerBullet(float x, float y, float vx, float vy,int type);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~PLayerBullet();
};

