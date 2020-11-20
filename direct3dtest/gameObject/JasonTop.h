#pragma once
#include "Player.h"

class JasonTop : public Player {
private:
	int controlState = 0;
public:
	JasonTop(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~JasonTop();
	void changeState(int stateId);
	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};