#include "Teleporter.h"

Teleporter::Teleporter(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->state = TELEPORTER_STOP;
	moveInterval = new GameTimer(400);
	stopInterval = new GameTimer(2000);
	this->HitPoint = 10;
	velocity = 48;
	this->vx = velocity;
	numberOfTeleportation = 0;
	this->dx = 0;
	this->dy = 0;
	this->direction = 0;
}

void Teleporter::render()
{
	Enemy::render();

}

void Teleporter::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	SharedData* sharedata =SharedData::getInstance();
	//GameObject::update(dt);
	this->dt = dt;
	short timerstate = moveInterval->update(dt);
	short timerstate2 = stopInterval->update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
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
					direction = 0;
				}
			}
		}

	}
	if (numberOfTeleportation == 0) {
		stopInterval->restart();
		this->state = TELEPORTER_STOP;

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
		tempx = 0.2 * tempx / tempc;
		tempy = 0.2 * tempy / tempc;
		new EnemyBullet(this->x + 10, this->y + 10, tempx, tempy, 1);
		numberOfTeleportation = (rand() % 5) + 5;
		direction = 0;
	}
	if (timerstate2 == TIMER_INACTIVE) {
		if (timerstate == TIMER_INACTIVE) {
			moveInterval->restart();
			if ((direction == 1) || (direction == -1))this->x += 48 * direction;
			else {
				this->y += 24 * direction;
			}
			this->state = TELEPORTER_MOVE;
			numberOfTeleportation--;
			direction = (rand() % 5) -2;
			switch (direction) {
			case 1:this->dx = velocity; this->dy = 0; break;
			case -1:this->dx = -velocity; this->dy = 0; break;
			case 2:this->dx = 0; this->dy = velocity; break;
			case -2:this->dx = 0; this->dy = -velocity; break;
			case 0: this->dx = 0; this->dy = 0; break;
			default: this->dx = 0; this->dy = 0; break;
			}
		}
	}

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
