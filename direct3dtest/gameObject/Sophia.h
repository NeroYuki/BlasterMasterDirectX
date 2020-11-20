#pragma once
#include "Player.h"
#define SOPHIA_JUMP_SPEED 0.05
class Sophia : public Player {
private:
	int controlState = 0;
public:
	Sophia(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Sophia();
	void changeState(int stateId);
	int getState() { return state; }
	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};