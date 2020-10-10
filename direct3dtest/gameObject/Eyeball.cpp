#include "Eyeball.h"

Eyeball::Eyeball(float x, float y, int hp) : Enemy(x, y, hp)
{

}

void Eyeball::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(EYEBALL_MOVE_LEFT);
	ani->render(x, y);
}

void Eyeball::update(DWORD dt)
{
}

Eyeball::~Eyeball()
{
}
