#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "../AnimationManger.h"
#include "../StateDictionary.h"
#include "../GlobalConstant.h"
#include "../CollisionHelper.h"
#include <algorithm>

class GameObject;
typedef GameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class GameObject {
protected:
	float x, y;		//position, should be a new class (CPoint?)
	float vx = 0.0, vy = 0.0;
	float dx = 0.0, dy = 0.0;
	int nx = 0, ny = 0;
	DWORD dt;
	int state = 0;

public:
	//constructor
	GameObject(float x, float y);

	void setPos(float x, float y) { this->x = x; this->y = y; }
	void setVelocity(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void getPos(float &x, float &y) { x = this->x; y = this->y; }
	void getVelocity(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	int getState() { return state; }

	void renderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(std::vector<LPGAMEOBJECT>* coObjects, std::vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right) = 0;
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void render() = 0;
	virtual void changeState(int stateId) { this->state = stateId; }
};