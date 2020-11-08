#include "Jumper.h"

Jumper::Jumper(float x, float y, int hp) :Enemy(x,y,hp)
{
}

void Jumper::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(JUMPER_MOVE_LEFT);
	ani->render(x, y);
}

void Jumper::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Jumper::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_JUMPER_HEIGHT;
	right = left + BBOX_JUMPER_WIDTH;
}

Jumper::~Jumper()
{
}
