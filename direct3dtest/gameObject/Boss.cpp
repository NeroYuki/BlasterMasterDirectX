#include "Boss.h"

Boss::Boss(float x, float y, int hp) :Enemy(x,y,hp)
{
	this->HitPoint = hp;
	shootInterval = new GameTimer(150);
	dyingTimer = new GameTimer(3000);
	this->state = BOSS_BODY;
	waiting =0;
	this->vx = 0.05;
	this->vy = -0.05;
	this->yLevel = y;
}

void Boss::render()
{
	LPANIMATION ani;
	LPANIMATION deadani,deadani2,deadani3;
	deadani = AnimationManager::getInstance()->get(GRENADE_EXPLOSION);
	deadani2 = AnimationManager::getInstance()->get(GRENADE_EXPLOSION);
	deadani3 = AnimationManager::getInstance()->get(GRENADE_EXPLOSION);

	ani = AnimationManager::getInstance()->get(state);
	if (this->invincible == 1) {
		int random = SharedData::getInstance()->getRandomNumber() ;
		int random1 = random % 30 - 15;
		int random2 = random % 50 - 25;
		int random3 = random % 25 - 12;
		deadani->render(x+random1+20, y+random1+20, D3DCOLOR_RGBA(128, 128, 222, 255));
		deadani2->render(x+random2+20, y+random2+20, D3DCOLOR_RGBA(128, 128, 222, 255));
		deadani3->render(x+random3+20, y+random3+20, D3DCOLOR_RGBA(128, 128, 222, 255));

		if (istakingdmg == 1)ani->render(x, y, D3DCOLOR_RGBA(128, 128, 222, 255));
		else ani->render(x, y);
	}
	else {
		if (istakingdmg == 1)ani->render(x, y, D3DCOLOR_RGBA(128, 128, 222, 255));
		else ani->render(x, y);
	}
}

void Boss::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (this->HitPoint <= 0) { this->invincible = 1, this->isDie = 2; }
	short dmgstate = dameTakenTimer->update(dt);
	short deadtimerstate = dyingTimer->update(dt);

	if (dmgstate == TIMER_INACTIVE) {
		if (dmgtaken != 0)
		{
			this->HitPoint -= dmgtaken;
			dmgtaken = 0;
			istakingdmg = 0;
			dameTakenTimer->restart();
		}
	}
	else if (dmgstate == TIMER_ACTIVE) {
		if (istakingdmg == 1)istakingdmg = 0;
		else istakingdmg = 1;
	}
	else if (dmgstate == TIMER_ENDED) {
		istakingdmg = 0;
	}


	if (deadtimerstate == TIMER_INACTIVE) {
		if (invincible == 1) {
			dyingTimer->restart();
		}
	}
	else if (deadtimerstate == TIMER_ACTIVE)
	{
		if (istakingdmg == 1)istakingdmg = 0;
		else istakingdmg = 1;
		this->vx = 0;
		this->vy = 0;
	}
	else if (deadtimerstate == TIMER_ENDED) {
		this->isDie = 1;
	}


	GameObject::update(dt);
	short timestate = shootInterval->update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
		if (this->y >= yLevel + 50) {
			vy = -0.05;
		}
	}
	else {
		//DebugOut("Collision occured\n");
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (coEventsResult.size() != 0) {

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Block*>(e->obj)) {
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (nx != 0) vx = -vx;
					if (ny != 0) vy = -vy;
				}

			}
		}
		else {
			y += dy;
			x += dx;
		}
	}


	float tempx = 1;
	float tempy = 1;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Player*>(coObjects->at(i)))
		{
			dynamic_cast<Player*>(coObjects->at(i))->getPos(tempx, tempy);
			tempx -= (this->x + 30);
			tempy -= (this->y + 10);
			break;
		}
	}

	float tempc = sqrt(tempx * tempx + tempy * tempy);
	tempx = 0.2 * tempx / tempc;
	tempy = 0.2 * tempy / tempc;
	if (invincible != 1)
	{
		if (timestate == TIMER_INACTIVE) {
			if (waiting == 0) {
				new EnemyBullet(this->x + 30, this->y + 10, tempx, tempy, 1);
			}
			if (waiting == 1) {
				new EnemyBullet(this->x + 30, this->y + 10, tempx, tempy, 1);
			}
			if (waiting == 2) {
				new EnemyBullet(this->x + 30, this->y + 10, tempx, tempy, 1);
			}
			if (waiting == 3) {
				new EnemyBullet(this->x + 30, this->y + 10, tempx, tempy, 1);
			}
			waiting++;
			shootInterval->restart();
		}
		if (waiting == 15)waiting = 0;
	}
}

void Boss::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + 64;
	right = left + 60;
}

void Boss::getLeftHand(float& x, float& y)
{
	x = this->x;
	y = this->y + 20;
}

void Boss::getRightHand(float& x, float& y)
{
	x = this->x+40;
	y = this->y + 20;
}

Boss::~Boss()
{
}
