#include "Bullet.h"

Bullet::Bullet(float x, float y, float vx, float vy) : GameObject(x, y) {
	this->HitPoint = 0;
}

Bullet::~Bullet()
{
}


void Bullet::FilterCollisionBlock(std::vector<LPCOLLISIONEVENT>& coEvents, std::vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	LPCOLLISIONEVENT minimum_x_event = nullptr;
	LPCOLLISIONEVENT minimum_y_event = nullptr;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (dynamic_cast<Block*>(c->obj) == nullptr) {
			continue;
		}

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; minimum_x_event = c; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; minimum_y_event = c; min_iy = i; rdy = c->dy;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) {
		if (dynamic_cast<Block*>(coEvents[i]->obj)) {
			LPCOLLISIONEVENT ci = coEvents[i];
			coEvents.erase(coEvents.begin() + i);
			i--;
			if (ci != minimum_x_event && ci != minimum_y_event) {
				delete ci;
			}
		}
	}

	if (minimum_x_event != nullptr) coEventsResult.push_back(minimum_x_event);
	if (minimum_y_event != nullptr) coEventsResult.push_back(minimum_y_event);


}
