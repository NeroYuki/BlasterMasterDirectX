#include "lightning.h"

lightning::lightning(float x, float y) : Bullet(x, y, vx, vy)
{
	this->x = x;
	this->y = y;
	this->state = SOPHIA_LIGHTNING;
	Lightningtimer = new GameTimer(100);
	bulletwidth = 20;
	bulletheight = 94;
	Lightningtimer->restart();
	BulletManager::getinstance()->addBullet(this);
}

void lightning::render()
{

	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void lightning::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

	GameObject::update(dt);
	short timestate = Lightningtimer->update(dt);

	for (UINT i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<Enemy*>(coObjects->at(i))) {
			Enemy* tempEnemy = dynamic_cast<Enemy*>(coObjects->at(i));
			float x1=0, x2=0, y1=0, y2=0;
			tempEnemy->GetBoundingBox(y1, x1, y2, x2);
			x1 =x1- this->x-15; x2 =x2- this->x; y1 =y1- this->y-64; y2=y2- this->y;
			if ((x1 < 0 && x2>0) && (y1 < 0 && y2>0)) {
				tempEnemy->GetHit(10);
			}
		}
	}

	if (timestate == TIMER_ENDED)
		BulletManager::getinstance()->removeBullet(this);
}

void lightning::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + bulletheight;
	right = left + bulletwidth;
}

lightning::~lightning()
{
}
