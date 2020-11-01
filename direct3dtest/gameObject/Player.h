#pragma once
#include "GameObject.h"
#define PLAYER_WALKING_SPEED 0.06

#define BBOX_PLAYER_WIDTH 20
#define BBOX_PLAYER_HEIGHT 20

class Player : public GameObject {
private:
	int controlState = 0;
public:
	Player(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Player();
	void changeState(int stateId);
	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }
	virtual void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};