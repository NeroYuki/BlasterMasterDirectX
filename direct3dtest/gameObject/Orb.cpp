#include "Orb.h"

Orb::Orb(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->vx = 0.3;
	this->vy = 0;
}

void Orb::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(ORB_MOVE_LEFT);
	ani->render(x, y);
}

void Orb::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::update(dt);
	//short insecttimerstate1 = insecttimer1->update(dt);
	//short insecttimerstate2 = insecttimer2->update(dt);

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
					//if (ny > 0) {
					//	vy = 0;
					//}
					//if (ny < 0) {
					//	if (vy < 0.1) {
					//		vy = 0;
					//	}
					//	else {
					//		vy = -vy / 2;
					//	}
					//}
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
