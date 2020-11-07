#include "Cannon.h"

Cannon::Cannon(float x, float y, int hp) : Enemy(x,y,hp)
{
}

void Cannon::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(CANNON_MOVE);
	ani->render(x, y);
}

void Cannon::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Cannon::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->x;
	left = this->y;
	bottom = top + BBOX_CANNON_HEIGHT;
	right = left + BBOX_CANNON_WIDTH;
}

Cannon::~Cannon()
{
}
