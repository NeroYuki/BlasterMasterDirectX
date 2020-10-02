#include "Dome.h"
#define DOME_MOVE_LEFT 301

Dome::Dome(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Dome::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(DOME_MOVE_LEFT);
	ani->render(x, y);
}

void Dome::update(DWORD dt)
{
}

Dome::~Dome()
{
}
