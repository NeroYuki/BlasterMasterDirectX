#include "Floater.h"

Floater::Floater(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Floater::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(FLOATER_MOVE_LEFT);
	ani->render(x, y);
}

void Floater::update(DWORD dt)
{
}

Floater::~Floater()
{
}
