#include "Mine.h"

Mine::Mine(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->state = MINE_TICK;
	this->x = x;
	this->y = y + 8;
	this->HitPoint = 1;
	explo = 0;
}

void Mine::render()
{

	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Mine::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (HitPoint < 0) {
		new EnemyBullet(this->x + 3, this->y, 0.075, 0, 3);
		new EnemyBullet(this->x + 3, this->y, -0.05, 0, 3);
		new EnemyBullet(this->x + 3, this->y, 0, 0, 3);
		this->isDie = 1;
	}
	GameObject::update(dt);
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
