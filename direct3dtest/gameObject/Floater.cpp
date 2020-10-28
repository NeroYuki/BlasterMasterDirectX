#include "Floater.h"

Floater::Floater(float x, float y, int hp) : Enemy(x, y, hp)
{
	vy = WALKING_SPEED;
	state = FLOATER_IDLE_LEFT;
}

void Floater::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Floater::update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	//bounding logic
	if (y <= 0) vy = WALKING_SPEED;
	else if (y >= SCREEN_HEIGHT - 20) vy = -WALKING_SPEED;

	if (vx > 0) {
		state = FLOATER_MOVE_RIGHT;
	}
	else if (vx < 0) {
		state = FLOATER_MOVE_LEFT;
	}
	else if (vy != 0) {
		if (state == FLOATER_IDLE_LEFT) state = FLOATER_MOVE_LEFT;
		else if (state == FLOATER_IDLE_RIGHT) state = FLOATER_MOVE_RIGHT;
	}
	else {
		if (state == FLOATER_MOVE_LEFT) state = FLOATER_IDLE_LEFT;
		else if (state == FLOATER_MOVE_RIGHT) state = FLOATER_IDLE_RIGHT;
	}
}

Floater::~Floater()
{
}
