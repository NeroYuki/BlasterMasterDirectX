#pragma once
#include "GameObject.h"
#include "../Debug.h"
#define PLAYER_WALKING_SPEED 0.06

#define BBOX_PLAYER_WIDTH 24
#define BBOX_PLAYER_HEIGHT 18

class Player : public GameObject {
protected:
	int controlState = 0;
	bool switchingSection = false;
	GameTimer* sectionSwitchingTimer;
public:
	Player(float x, float y, int hp);
	void render();
	virtual void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Player();
	virtual void changeState(int stateId);
	int getState() { return state; }
	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right) = 0;
};