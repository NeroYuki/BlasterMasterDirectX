#pragma once
#include "Enemy.h"

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
};