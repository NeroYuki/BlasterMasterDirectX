#include "Orb.h"
#define ORB1_MOVE_LEFT 901

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Orb::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(ORB1_MOVE_LEFT);
	ani->render(x, y);
}

void Orb::update(DWORD dt)
{
}

Orb::~Orb()
{
}
