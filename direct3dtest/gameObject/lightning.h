#pragma once
class BulletManager;
#include "Bullet.h"
#include "Player.h"
#include "BulletManager.h"
#include "Enemy.h"
class lightning : public Bullet {
protected:
	GameTimer* Lightningtimer;
	int bulletheight , bulletwidth ;
public:
	lightning(float x, float y);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
	~lightning();
};