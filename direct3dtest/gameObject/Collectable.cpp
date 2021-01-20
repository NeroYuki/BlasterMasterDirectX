#include "Collectable.h"

Collectable::Collectable(float x, float y, int type,int value) : GameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->value = value;
	switch (type) {
	case 1:this->state = POWER_UP_HP; break;
	case 2:this->state = POWER_UP_GUN_UPGRADE; break;
	case 3:this->state = POWER_UP_HOMINGMISSLE; break;
	case 4:this->state = POWER_UP_X3MISSLE; break;
	case 5:this->state = POWER_UP_THUNDER; break;
	case 6:this->state = POWER_UP_HOVER; break;
	default: this->state = POWER_UP_HP; break;
	}
}

void Collectable::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Collectable::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	SharedData* instance = SharedData::getInstance();
	if (this->isPicked == 1) {
		switch (type)
		{
		case 3: instance->homingMissle += value; break;
		case 4:	instance->x3Missle += value; break;
		case 5:	instance->lightning += value; break;
		default:
			break;
		}
		this->isDie = 1;
	}
}

void Collectable::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + 16;
	right = left + 16;

}

Collectable::~Collectable()
{
}

void  Collectable::getPicked(int &t,int &v)
{
	t = type;
	v = value;
	this->isPicked = 1;
}
