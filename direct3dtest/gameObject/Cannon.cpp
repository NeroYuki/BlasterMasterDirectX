#include "Cannon.h"
#define Cannon_move 601 
Cannon::Cannon(float x, float y, int hp) : Enemy(x,y,hp)
{
}

void Cannon::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(Cannon_move);
	ani->render(x, y);
}

void Cannon::update(DWORD dt)
{
}

Cannon::~Cannon()
{
}
