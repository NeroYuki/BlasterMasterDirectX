#pragma once
#include "Enemy.h"

#define IDLE_STATE 0

class Player : public GameObject {
private:
public:
	Player(float x, float y, int hp);
	void render();
	void update(DWORD dt);
	~Player();
	void changeState(int stateId);
};