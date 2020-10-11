#include "Worm.h"

Worm::Worm(float x, float y, int hp) : Enemy(x, y, hp)
{
	vx = 0.03;
}

void Worm::render()
{
	LPANIMATION ani;
	if (vx > 0) {
		ani = AnimationManager::getInstance()->get(WORM_MOVE_LEFT);
	}
	else if (vx < 0) {
		ani = AnimationManager::getInstance()->get(WORM_MOVE_RIGHT);
	}
	else {
		ani = AnimationManager::getInstance()->get(WORM_IDLE);
	}
	ani->render(x, y);
}

void Worm::update(DWORD dt)
{
	x += vx * dt;
	if (x <= 0) vx = 0.03;
	else if (x >= 320) vx = -0.03;
}

Worm::~Worm()
{
}
