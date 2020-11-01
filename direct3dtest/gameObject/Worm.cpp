#include "Worm.h"

Worm::Worm(float x, float y, int hp) : Enemy(x, y, hp)
{
	vx = 0.03;
	state = WORM_IDLE_LEFT;
}

void Worm::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Worm::update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	//bounding logic
	if (x <= 0) vx = 0.03;
	else if (x >= SCREEN_WIDTH - 18) vx = -0.03;

	if (vx > 0) {
		state = WORM_MOVE_RIGHT;
	}
	else if (vx < 0) {
		state = WORM_MOVE_LEFT;
	}
	else {
		if (state == WORM_MOVE_LEFT) state = WORM_IDLE_LEFT;
		else if (state == WORM_MOVE_RIGHT) state = WORM_IDLE_RIGHT;
	}
}

void Worm::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->x;
	left = this->y;
	bottom = top + BBOX_WORM_HEIGHT;
	right = left + BBOX_WORM_WIDTH;
}

Worm::~Worm()
{
}
