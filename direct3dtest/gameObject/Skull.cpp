#include "Skull.h"

Skull::Skull(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Skull::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(SKULL_MOVE_LEFT);
	ani->render(x, y);
}

void Skull::update(DWORD dt)
{
}

Skull::~Skull()
{
}
