#pragma once
#include "GameObject.h"
#include "Player.h"
#include "EnemyBullet.h"
#include "CollectableManager.h"
#include "../SharedData.h"

#define WALKING_SPEED 0.03

class Enemy : public GameObject {
protected:
	int HitPoint;
	GameTimer* dameTakenTimer;
	GameTimer* dyingTimer;
	int istakingdmg;
	int dmgtaken = 0;
	int invincible = 0;
public:
	Enemy(float x, float y, int hp);
	virtual void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects) ;
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right) = 0;
	~Enemy();
	void FilterCollisionBlock(std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	void GetHit(int n);
};