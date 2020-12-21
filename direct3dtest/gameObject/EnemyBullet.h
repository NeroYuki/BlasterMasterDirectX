#pragma once
#pragma once
class BulletManager;
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "Enemy.h"
class EnemyBullet : public Bullet {
protected:
	int HitPoint;
	int active = 1;
	GameTimer* surviveTime;
	GameTimer* exploTime;
	int bulletheight = 6, bulletwidth = 6;
	int bulletstate = 0;
	int enemytype = 0;
public:
	EnemyBullet(float x, float y, float vx, float vy, int type);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~EnemyBullet();
};

