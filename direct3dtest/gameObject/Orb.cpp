#include "Orb.h"

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
	moveInterval = new GameTimer(1000);
	stopinterval = 0;

	int random =SharedData::getInstance()->getRandomNumber();
	this->type = random % 2 + 1;
	if (type == 1) {
		this->state = ORB_CIRCLE;
	}
	else {
		this->state = ORB_LEFT_2;
		moveInterval = new GameTimer(300);
	}
	spawnPlace = 1;
}

void Orb::render()
{
	Enemy::render();
}

void Orb::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	GameObject::update(dt);
	short timestate2 = moveInterval->update(dt);

	if (this->isDie == 2) this->isDie = 1;

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	coEventsResult.clear();
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

		// TODO: This is a very ugly designed function!!!! (i dont care as long as it works bruh)
		FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back player if collides with a moving objects, what if player is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
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
	if (type == 1) {
		int random2;
		random2 = SharedData::getInstance()->getRandomNumber();
		if (timestate2 == TIMER_INACTIVE) {
			if (stopinterval == 3)stopinterval = 0;
			if (stopinterval == 0) {
				if (random2 % 2 == 0) {
					this->vy = 0;
					this->vx = 0.1;
					this->state = ORB_RIGHT_1;
				}
				else {
					this->vy = 0;
					this->vx = -0.1;
					this->state = ORB_LEFT_1;

				}
			}
			else if (stopinterval == 1)
			{
				if (random2 % 2 == 0) {
					this->vy = 0.025;
					this->vx = 0;
				}
				else {
					this->vy = -0.025;
					this->vx = 0;
				}

				this->state = ORB_CIRCLE;
			}
			stopinterval++;
			moveInterval->restart();
		}
	}
	else if (type == 2) {
		if (timestate2 == TIMER_INACTIVE) {
			float tempx = 1;
			float tempy = 1;
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (dynamic_cast<Player*>(coObjects->at(i)))
				{
					dynamic_cast<Player*>(coObjects->at(i))->getPos(tempx, tempy);
					break;
				}
			}
			if (this->y > tempy) {
				this->vy = -0.05;
			}
			else{
				this->vy = 0.05;
			}
			if (this->x > tempx) {
				this->vx = -0.1;
				state = ORB_LEFT_2;
			}
			else {
				this->vx = 0.1;
				state = ORB_RIGHT_2;
			}
			moveInterval->restart();
		}
	}

}

void Orb::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_ORB_HEIGHT;
	right = left + BBOX_ORB_WIDTH;
}

Orb::~Orb()
{
}
