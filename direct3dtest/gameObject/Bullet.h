#pragma once
#include "GameObject.h"
#include "Block.h"
#include "DestrucableBlock.h"
class Bullet : public GameObject {
protected:
	int HitPoint;
	GameTimer* surviveTime;
public:
	Bullet(float x, float y, float vx, float vy);
	virtual void render()=0;
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)=0 ;
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right)=0;
	void FilterCollisionBlock(std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	~Bullet();
};

