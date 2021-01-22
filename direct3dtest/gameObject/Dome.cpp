#include "Dome.h"

Dome::Dome(float x, float y, int hp) : Enemy(x, y, hp)
{
	vx = 0;
	vy = 0.05;
	state = WORM_IDLE_LEFT;
	domestate = 1;
	spawnPlace = 1;
	ontopwall = 1;
	godown == 1;
}

void Dome::render()
{
	Enemy::render();

}

void Dome::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);

	if (this->isDie == 2) this->isDie = 1;
	//GameObject::update(dt);
	//this->dt = dt;
	//dx = 0;
	//dy = 0;
	//vx = 0;
	//vy = 0;

	//goup = 0;
	//godown = 0;
	//goleft = 0;
	//goright = 0;
	
	//std::vector<LPCOLLISIONEVENT> coEvents;
	//std::vector<LPCOLLISIONEVENT> coEventsResult;
	//coEvents.clear();
	//CalcPotentialCollisions(coObjects, coEvents);
	//float min_tx, min_ty, nx = 0, ny = 0;
	//float rdx = 0;
	//float rdy = 0;
	//FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	//if (coEventsResult.size() != 0) {
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];
	//		if (dynamic_cast<Block*>(e->obj)) {
	//			if (ny == 1) {
	//				goleft = 1;
	//			}
	//			else if (ny == -1) {
	//				goright = 1;
	//			}
	//			if (nx == 1) {
	//				goup = 1;
	//			}
	//			else if (nx == -1) {
	//				godown = 1;
	//			}
	//		}
	//	}
	//}
	//else {
	//	if (ontopwall == 1) ontopwall = 0;
	//	if (onrightwall == 1) onrightwall =0;
	//	if (onleftwall == 1) onleftwall = 0;
	//	if (onbtottomwall == 1)onbtottomwall =0;
	//}
	//



	//checkdirection();
	//this->dx = vx * dt;
	//this->dy = dy * dt;
	//coEvents.clear();
	//coEventsResult.clear();
	//CalcPotentialCollisions(coObjects, coEvents);

	//if (coEvents.size() == 0) {
	//	x += dx;
	//	y += dy;
	//}
	//else {
	//	float min_tx, min_ty, nx = 0, ny = 0;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!! (i dont care as long as it works bruh)
	//	FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	if (coEventsResult.size() != 0) {
	//		for (UINT i = 0; i < coEventsResult.size(); i++)
	//		{
	//			LPCOLLISIONEVENT e = coEventsResult[i];
	//			if (dynamic_cast<Block*>(e->obj)) {
	//				x += min_tx * dx + nx * 0.4f;
	//				y += min_ty * dy + ny * 0.4f;
	//				if (ny ==1) { onbtottomwall = 1; }
	//				else if (ny == -1) {
	//					onbtottomwall = 1;
	//				}
	//				if (nx ==1) {
	//					onleftwall = 1;
	//				}
	//				else if (nx ==-1 ){
	//					onrightwall = 1;
	//				}
	//			}
	//		}
	//	}
	//	else {
	//		y += dy;
	//		x += dx;
	//	}
	//}
	//if (ontopwall == 1) { vx = 0.2; vy = 0; }
	//if (onrightwall == 1) { vx = 0; vy = 0.2; }
	//if (onleftwall == 1) { vx = 0; vy = -0.2; }
	//if (onbtottomwall == 1) { vx = -0.2; vy = 0; }



}

void Dome::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + 16;
	right = left + 16;
}


Dome::~Dome()
{
}

void Dome::checkdirection() {
	vx = 0;
	vy = 0;
	if (ontopwall == 1 && goleft == 1) {
		vx = -0.1;
	}
	if (ontopwall == 1 && goright == 1) {
		vx = 0.1;
	}
	if (onbtottomwall == 1 && goleft == 1) {
		vx = -0.1;
	}
	if (onbtottomwall == 1 && goright == 1) {
		vx = 0.1;
	}
	if (onrightwall == 1 && goup == 1) {
		vy = -0.1;
	}
	if (onrightwall == 1 && godown == 1) {
		vx = 0.1;
	}
	if (onleftwall == 1 && goup == 1) {
		vx = -0.1;
	}
	if (onleftwall == 1 && godown == 1) {
		vx = 0.1;
	}
}