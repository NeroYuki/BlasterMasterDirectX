#include "Jumper.h"
#define JUMPER1_MOVE_LEFT 401

Jumper::Jumper(float x, float y, int hp) :Enemy(x,y,hp)
{
}

void Jumper::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(JUMPER1_MOVE_LEFT);
	ani->render(x, y);
}

void Jumper::update(DWORD dt)
{
}

Jumper::~Jumper()
{
}
