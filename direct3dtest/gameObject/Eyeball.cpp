#include "Eyeball.h"

Eyeball::Eyeball(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->HitPoint = hp;
	shootInterval = new GameTimer(2000);
	moveInterval = new GameTimer(1000);
	stopinterval = 0;
	this->state = EYE_IDLE;
	spawnPlace = 2;
}

void Eyeball::render()
{
	Enemy::render();
}

void Eyeball::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	GameObject::update(dt);
	short timestate = shootInterval->update(dt);
	short timestate2 = moveInterval->update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
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
	int tempvx, tempvy;
	tempvx=SharedData::getInstance()->getRandomNumber();
	tempvy =SharedData::getInstance()->getRandomNumber();
	if (timestate2 == TIMER_INACTIVE) {
		if (stopinterval == 2)stopinterval = 0;
		if(stopinterval == 0){
			this->vx =(float)(tempvx%15) / 100;
			this->vy =(float)(tempvy%15)/ 100;
			this->state = EYE_IDLE;
		}
		else if(stopinterval ==1)
		{
			this->vx = 0;
			this->vy = 0;
			this->state = EYE_MOVE;
		}
		stopinterval++;
		moveInterval->restart();
	}
	float tempx = 1;
	float tempy = 1;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Player*>(coObjects->at(i)))
		{
			dynamic_cast<Player*>(coObjects->at(i))->getPos(tempx, tempy);
			tempx -= this->x;
			tempy -= this->y;
			break;
		}
	}
	float tempc = sqrt(tempx * tempx + tempy * tempy);
	tempx =0.2* tempx / tempc;
	tempy =0.2* tempy / tempc;
	if (timestate == TIMER_INACTIVE) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_TELEPORTER_SHOOTING);
		new EnemyBullet(this->x + 10, this->y + 10, tempx, tempy, 1);
		shootInterval->restart();
	}
}

void Eyeball::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_EYEBALL_HEIGHT;
	right = left + BBOX_EYEBALL_WIDTH;
}

Eyeball::~Eyeball()
{
}
