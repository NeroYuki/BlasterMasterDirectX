#include "Teleporter.h"

Teleporter::Teleporter(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Teleporter::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(TELEPORTER_TELEPORT);
	ani->render(x, y);
}

void Teleporter::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
}

void Teleporter::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_TELEPORTER_HEIGHT;
	right = left + BBOX_TELEPORTER_WIDTH;
}

Teleporter::~Teleporter()
{
}
