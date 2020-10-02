#include "Mine.h"
#define MINE_FLICK 1

Mine::Mine(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Mine::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(MINE_FLICK);
	ani->render(x, y);
}

void Mine::update(DWORD dt)
{
}
