#include "Worm.h"
#define WORM_MOVE_LEFT 101

Worm::Worm(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Worm::render()
{
	LPANIMATION ani;
	
	ani = AnimationManager::getInstance()->get(WORM_MOVE_LEFT);
	ani->render(x, y);
}

void Worm::update(DWORD dt)
{
}

Worm::~Worm()
{
}
