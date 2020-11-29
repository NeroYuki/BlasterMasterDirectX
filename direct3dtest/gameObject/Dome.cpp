#include "Dome.h"

Dome::Dome(float x, float y, int hp) : Enemy(x, y, hp)
{
	vx = -0.03;
	vy = 0.00;
	state = DOME_IDLE_DOWN_LEFT;
	domestate = 1;
}

void Dome::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Dome::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (vx > 0) {
		state = WORM_MOVE_RIGHT;
	}
	else if (vx < 0) {
		state = WORM_MOVE_LEFT;
	}
	else {
		if (state == WORM_MOVE_LEFT) state = WORM_IDLE_LEFT;
		else if (state == WORM_MOVE_RIGHT) state = WORM_IDLE_RIGHT;
	}

	velx = 32;
	vely = 32;
	if (isonwall) {
		if (domestate == 1 ) {

			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (dynamic_cast<Block*>(coObjects->at(i)))
				{
					float px, py;
					Block* p = dynamic_cast<Block*>(coObjects->at(i));
					p->getPos(px, py);
					px = px - x;
					py = py - y;
					if (py > 0 && py < 16 && px < velx && px > 16) {
						velx = px; vely = py;
					}
				}
			}
			if (velx > 16&&velx<20) {
				domestate = 0;
				vx = 0.01;
				vy = 0.03;
			}
		}
		else if (domestate == 2) {
			for (UINT i = 0; i < coObjects->size(); i++)
			{
				if (dynamic_cast<Block*>(coObjects->at(i)))
				{
					float px, py;
					Block* p = dynamic_cast<Block*>(coObjects->at(i));
					p->getPos(px, py);
					px = px - x;
					py = py - y;
					if (py>0 && py < 16 && px < velx && px > 16) {
						velx = px; vely = py;
					}
				}
			}
			domestate = 1;
			vx = -0.03;
			vy = 0.01;
		}
		else if (domestate == 3)
		{
			domestate = 2;
			vy = -0.03;
			vx = -0.01;
		}
		else if (domestate == 0)
		{
			domestate = 3;
			vx = 0.03;
			vy = -0.01;
		}

	}
	

	//if (domestate == 0) {
	//	vy = 0.03;
	//}
	//else 	if (domestate ==1) {
	//	vx = -0.03;
	//}
	//else if (domestate == 2) {
	//	vy = -0.03;
	//}
	//else if (domestate == 3) {
	//	vx = 0.03;
	//}
	GameObject::update(dt);
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//after this method, coEvents SHOULD only contain collision event thats the target is not a block (ie Entity) 
		//and coEventsResult is now contain closest collision to a block to adjust player position accordingly
		if (coEventsResult.size() != 0) {
			if (domestate == 1 && nx == 1) {
				domestate = 2;
				vy = -0.03;
				vx = -0.01;
				isonwall = true;
			}
			if (domestate == 2 && ny == 1) {
				domestate = 3;
				vx = 0.03;
				vy = -0.01;
				isonwall = true;
			}
			if (domestate == 3 && nx == -1)
			{
				domestate = 0;
				vx = 0.01;
				vy = 0.03;
				isonwall = true;
			}
			if (domestate == 0 && ny == -1)
			{
				domestate = 1;
				vx = -0.03;
				vy = 0.01;
				isonwall = true;
			}
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0) vx = 0;
			else if (ny != 0) vy = 0;
		}
		else {
			y += dy;
			x += dx;
		}

		for (UINT i = 0; i < coEvents.size(); i++) {
			DebugOut("Entity collision\n");
		}
	}
}

void Dome::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_DOME_HEIGHT;
	right = left + BBOX_DOME_WIDTH;
}


Dome::~Dome()
{
}
