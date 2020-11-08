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

void Boss::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Boss::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_BOSS_HEIGHT;
	right = left + BBOX_BOSS_WIDTH;
}

Boss::~Boss()
{
}
