#include "Boss.h"

Boss::Boss(float x, float y, int hp) :Enemy(x,y,hp)
{
}

void Boss::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(1);
	ani->render(x, y);
}

void Boss::update(DWORD dt)
{
}

Boss::~Boss()
{
}
