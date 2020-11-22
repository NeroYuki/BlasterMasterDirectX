#include "Mine.h"

Mine::Mine(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Mine::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(MINE_FLICK);
	ani->render(x, y);
}

void Mine::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Mine::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_MINE_HEIGHT;
	right = left + BBOX_MINE_WIDTH;
}

Mine::~Mine()
{
}
