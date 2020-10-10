#include "Cannon.h"

Cannon::Cannon(float x, float y, int hp) : Enemy(x,y,hp)
{
}

void Cannon::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(CANNON_MOVE);
	ani->render(x, y);
}

void Cannon::update(DWORD dt)
{
}

Cannon::~Cannon()
{
}
