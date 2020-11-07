#include "Skull.h"

Skull::Skull(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Skull::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(SKULL_MOVE_LEFT);
	ani->render(x, y);
}

void Skull::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Skull::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->x;
	left = this->y;
	bottom = top + BBOX_SKULL_HEIGHT;
	right = left + BBOX_SKULL_WIDTH;
}

Skull::~Skull()
{
}
