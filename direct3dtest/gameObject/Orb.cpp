#include "Orb.h"

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Orb::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(ORB_MOVE_LEFT);
	ani->render(x, y);
}

void Orb::update(DWORD dt)
{
}

void Orb::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->x;
	left = this->y;
	bottom = top + BBOX_ORB_HEIGHT;
	right = left + BBOX_ORB_WIDTH;
}

Orb::~Orb()
{
}
