#pragma once
#include "Player.h"
#include "Teleporter.h"

class JasonTop : public Player {
private:
	int facing = 0;
	GameTimer* bulletDelayTimer;
	GameTimer* grenadeDelayTimer; 
	int bullettype = 2;
public:
	JasonTop(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~JasonTop();
	void changeState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};