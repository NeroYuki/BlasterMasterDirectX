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

void Eyeball::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Eyeball::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_EYEBALL_HEIGHT;
	right = left + BBOX_EYEBALL_WIDTH;
}

Eyeball::~Eyeball()
{
}
