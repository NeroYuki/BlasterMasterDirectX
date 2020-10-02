#include "Insect.h"
#define INSECT_MOVE_LEFT 501


Insect::Insect(float x, float y, int hp) : Enemy(x, y, hp)
{

}

void Insect::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(INSECT_MOVE_LEFT);
	ani->render(x, y);
}

void Insect::update(DWORD dt)
{
}

Insect::~Insect()
{
}
