#include "Floater.h"

Floater::Floater(float x, float y, int hp) : Enemy(x, y, hp)
{	vx = 0.02;
	vy = 0.05;
	state = FLOATER_IDLE_LEFT;
	shoottimer = new GameTimer(2000);
	this->HitPoint = 5;
	spawnPlace = 1;
}

void Floater::render()
{
	Enemy::render();

}

void Floater::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	float tempx = 1;
	float tempy = 1;
	//x += vx * dt;
	//y += vy * dt;

	//bounding logic
	//if (y <= 0) vy = WALKING_SPEED;
	//else if (y >= SCREEN_HEIGHT - 20) vy = -WALKING_SPEED;

	if (vx > 0) {
		state = FLOATER_MOVE_RIGHT;
	}
	else if (vx < 0) {
		state = FLOATER_MOVE_LEFT;
	}
	//else if (vy != 0) {
	//	if (state == FLOATER_IDLE_LEFT) state = FLOATER_MOVE_LEFT;
	//	else if (state == FLOATER_IDLE_RIGHT) state = FLOATER_MOVE_RIGHT;
	//}
	//else {
	//	if (state == FLOATER_MOVE_LEFT) state = FLOATER_IDLE_LEFT;
	//	else if (state == FLOATER_MOVE_RIGHT) state = FLOATER_IDLE_RIGHT;
	//}

	GameObject::update(dt);
	shoottimer->update(dt);
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

	if (shoottimer->peekState() == TIMER_INACTIVE) {
		new EnemyBullet(this->x + 10, this->y + 10, tempx, tempy, 1);
		shoottimer->restart();
	}

}

void Floater::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_FLOATER_HEIGHT;
	right = left + BBOX_FLOATER_WIDTH;
}

Floater::~Floater()
{
}
