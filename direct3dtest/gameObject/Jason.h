#pragma once
#include "Player.h"
#define JASON_JUMP_SPEED 0.05

class Jason : public Player {
private:
	int controlState = 0;
	bool is_craw = false;
public:
	Jason(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Jason();
	void setCrawState(bool isCraw) { is_craw = isCraw; }
	bool getCrawState() { return is_craw; }
	void changeState(int stateId);
	int getState() { return state; }
	int getControlState() { return controlState; }
	void setControlState(int controlState) { this->controlState = controlState; }
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};