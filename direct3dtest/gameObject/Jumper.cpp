#include "Jumper.h"

Jumper::Jumper(float x, float y, int hp) :Enemy(x,y,hp)
{
}

void Jumper::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(JUMPER_MOVE_LEFT);
	ani->render(x, y);
}

void Jumper::update(DWORD dt)
{
}

Jumper::~Jumper()
{
}
