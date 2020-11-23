#pragma once
#include "Player.h"
#include "Jason.h"
#define SOPHIA_JUMP_SPEED 0.3
#define SOPHIA_MOVE_ACCEL 0.01
#define SOPHIA_MOVE_SPEED_CAP 0.12

#define BBOX_SOPHIA_HEIGHT 18
#define BBOX_SOPHIA_WIDTH 26

class Sophia : public Player {
private:
	bool isOnAir = false;
	//movingState for the wheel, inherited state for the body 
	int movingState = 0;
	GameTimer* turningTimer;
	GameTimer* gunRaiseTimer;
public:
	Sophia(float x, float y, int hp);
	void render();
	void update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects);
	~Sophia();
	void changeState(int stateId);
	void changeMovingState(int stateId);
	void GetBoundingBox(float& top, float& left, float& bottom, float& right);
};