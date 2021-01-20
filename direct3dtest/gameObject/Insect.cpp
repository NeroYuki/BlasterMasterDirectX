#include "Insect.h"

Insect::Insect(float x, float y, int hp) : Enemy(x, y, hp)
{
	insectState = 1; // flying up
	vx = -0.005;
	vy = 0.05;
	insecttimer1 = new GameTimer(900);
	insecttimer2 = new GameTimer(100);
	state = INSECT_IDLE_LEFT;
}

void Insect::render()
{
	Enemy::render();
}

void Insect::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	if (insectState == 0) {
		vy +=0.01;
	}
	GameObject::update(dt);
	short insecttimerstate1 = insecttimer1->update(dt);
	short insecttimerstate2 = insecttimer2->update(dt);

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
					if (ny > 0) {
						vy = 0;
						insectState = 0;
					}
					if (ny < 0) {
						if (vy < 0.1) {
							vy = 0;
							insectState = 1;
						}
						else {
							vy = -vy / 2;
						}
					}
					if (nx != 0) {
						vx = -vx;
					}

				}
			}
		}
		else {
			y += dy;
			x += dx;
		}
	}

	if (insectState == 1) {
		if (insecttimerstate1 == TIMER_INACTIVE)
		{
			insecttimer1->restart();
			vy = -0.02;
		}
		else if (insecttimerstate1 == TIMER_ENDED) {
			insectState = 2;
		}

	}
	else if (insectState == 2) {
		if (insecttimerstate2 == TIMER_INACTIVE)
		{
			insecttimer2->restart();
			vy = 0.06;
		}
		else if (insecttimerstate2 == TIMER_ENDED) {
			insectState = 1;
		}
	}

	if (vx < 0) {
		if (state == INSECT_IDLE_LEFT) state = INSECT_MOVE_LEFT;
		else state = INSECT_IDLE_LEFT;
	}
	else if (vx>0) {
		if (state == INSECT_IDLE_RIGHT) state = INSECT_MOVE_RIGHT;
		else state = INSECT_IDLE_RIGHT;
	}
}

void Insect::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_INSECT_HEIGHT;
	right = left + BBOX_INSECT_WIDTH;
}

Insect::~Insect()
{
}
