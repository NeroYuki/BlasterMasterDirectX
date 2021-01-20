#include "Skull.h"

Skull::Skull(float x, float y, int hp) : Enemy(x, y, hp)
{
	state = SKULL_MOVE_LEFT;
	skulltimer1 = new GameTimer(3000);
	skulltimer2 = new GameTimer(200);
	this->vx = -0.1;
	this->vy = 0;

}

void Skull::render()
{
	Enemy::render();

}

void Skull::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	float tempx = 1;
	float tempy = 1;
	GameObject::update(dt);
	short timerstate1= skulltimer1->update(dt);
	//skulltimer2->update(dt);

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
						if (facing == -1) vx = -0.1;
						else if (facing == 1) vx = 0.1;
						skullstate = 3;
					}
					if (ny < 0) { 
					}
					if (nx != 0) {
						vx = -vx;
						facing = -facing;
					}
				}
			}
		}
		else {
			y += dy;
			x += dx;
		}
	}
	for (UINT i = 0;i < coObjects->size(); i++)
	{
		if (dynamic_cast<Player*>(coObjects->at(i)))
		{
			dynamic_cast<Player*>(coObjects->at(i))->getPos(tempx, tempy);

			break;
		}
	}

	if (this->x > tempx-8 && (this->x < tempx +8)&& (skullstate ==1)) {
		skullstate = 2;
		vx = 0;
		vy = -0.1;
		this->facing = -facing;
		new EnemyBullet(this->x + 8, this->y + 16, 0.05 * facing, 0, 2);
		SoundManager::getInstance()->Play(eSoundId::SOUND_SKULL_BOMBING);
	}
	if (skullstate == 3) {
		if (timerstate1 == TIMER_INACTIVE) skulltimer1->start();
		else if (timerstate1 == TIMER_ENDED) skullstate = 1;
	}
	if(facing == -1){
		if (skullstate == 2) { this->state = SKULL_OPEN_LEFT; }
		else this->state = SKULL_MOVE_LEFT;
	}
	else if(facing == 1)
	{
		if (skullstate == 2) { this->state = SKULL_OPEN_RIGHT; }
		else this->state = SKULL_MOVE_RIGHT;
	}
}

void Skull::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_SKULL_HEIGHT;
	right = left + BBOX_SKULL_WIDTH;
}

Skull::~Skull()
{
}
