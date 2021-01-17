#pragma once
#include "GameObject.h"
#include "../Debug.h"
#include "Portal.h"
#include "PlayerBullet.h"
#include "lightning.h"
#include "Ladder.h"
#include "ScenePortal.h"

#define PLAYER_WALKING_SPEED 0.06

#define BBOX_PLAYER_WIDTH 24
#define BBOX_PLAYER_HEIGHT 18

class Player : public GameObject {
protected:
	int controlState = 0;
	int activeSection = 0;
	bool ignoreCollision = false;
	bool ignoreInput = false;
	int forceControlState = 0;
	int hitpoint = 8;
	int upgrade = 1;
public:
	Player(float x, float y, int hp);
	void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Player();
	virtual void changeState(int stateId);
	int getState() { return state; }

	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }

	int getActiveSection() { return activeSection; }
	void setActiveSection(int inp) { this->activeSection = inp; }

	void setIgnoreCollision(bool inp) { this->ignoreCollision = inp; }
	void setIgnoreInput(bool inp) { this->ignoreInput = inp; }

	void setForceControlState(int inp) { this->forceControlState = inp; }

	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right) = 0;

	void FilterCollisionBlock(std::vector<LPCOLLISIONEVENT> &coEvents, 
		std::vector<LPCOLLISIONEVENT> &coEventsResult, 
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	void PlayerGetHit(int dmg) { this->hitpoint -= dmg; }
	void PlayerHeal(int value) { this->hitpoint += value; if (hitpoint > 8)hitpoint = 8; }
	void GetPlayerHitPoint(int& heatlhpoint) { heatlhpoint = this->hitpoint; }
};