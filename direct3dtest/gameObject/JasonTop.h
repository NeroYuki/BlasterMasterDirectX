#pragma once
#include "Player.h"
#include "Portal.h"

class JasonTop : public Player {
private:
public:
	JasonTop(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~JasonTop();
	void changeState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};