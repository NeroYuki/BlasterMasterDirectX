#pragma once
#include "Player.h"
#define SOPHIA_JUMP_SPEED 0.05
#define BBOX_SOPHIA_HEIGHT 18
#define BBOX_SOPHIA_WIDTH 26

class Sophia : public Player {
private:
public:
	Sophia(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Sophia();
	void changeState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};