#include "Dome.h"

Dome::Dome(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Dome::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(DOME_MOVE_LEFT_FLOOR);
	ani->render(x, y);
}

void Dome::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Dome::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_DOME_HEIGHT;
	right = left + BBOX_DOME_WIDTH;
}

Dome::~Dome()
{
}
