#include "Insect.h"

Insect::Insect(float x, float y, int hp) : Enemy(x, y, hp)
{

}

void Insect::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(INSECT_MOVE_LEFT);
	ani->render(x, y);
}

void Insect::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Insect::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->x;
	left = this->y;
	bottom = top + BBOX_INSECT_HEIGHT;
	right = left + BBOX_INSECT_WIDTH;
}

Insect::~Insect()
{
}
