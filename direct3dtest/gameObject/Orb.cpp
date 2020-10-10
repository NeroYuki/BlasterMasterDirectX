#include "Orb.h"

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Orb::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(ORB_MOVE_LEFT);
	ani->render(x, y);
}

void Orb::update(DWORD dt)
{
}

Orb::~Orb()
{
}
