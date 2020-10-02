#include "Teleporter.h"
#define TELEPORTER_TELEPORT 1201

Teleporter::Teleporter(float x, float y, int hp) : Enemy(x, y, hp)
{
}

void Teleporter::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(TELEPORTER_TELEPORT);
	ani->render(x, y);
}

void Teleporter::update(DWORD dt)
{
}

Teleporter::~Teleporter()
{
}
