#include "Orb.h"

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->vx = 0.3;
	this->vy = 0;
}

void Orb::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(ORB_MOVE_LEFT);
	ani->render(x, y);
}

void Orb::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

}

void Orb::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_ORB_HEIGHT;
	right = left + BBOX_ORB_WIDTH;
}

Orb::~Orb()
{
}
