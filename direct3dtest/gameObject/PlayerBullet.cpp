#include "PlayerBullet.h"
PLayerBullet::PLayerBullet(float x, float y, float vx, float vy,int type,int direction) : Bullet(x,y,vx,vy) {

	this->HitPoint = 0;
	surviveTime = new GameTimer(2000);
	exploTime = new GameTimer(200);
	TurningTime = new GameTimer(100);
	TurningTime2 = new GameTimer(200);
	if (type == 1) {
		this->bullettype = 1;
		if (direction == 1) {
			state = SOPHIA_BULLET_RIGHT;
			this->vx = 0.25;
			this->vy = 0;
			bulletwidth = 26;
			bulletheight = 8;
		}
		if (direction == 2) {
			state = SOPHIA_BULLET_LEFT;
			this->vx = -0.25;
			this->vy = 0;
			bulletwidth = 26;
			bulletheight = 8;
		}
		if (direction == 3) {
			state = SOPHIA_BULLET_UP;
			this->vx = 0;
			this->vy = -0.25;
			bulletwidth = 8;
			bulletheight = 26;
		}
	}
	if (type == 2)
	{
		this->bullettype = 2;
		if (direction == 1) {
			state = SOPHIA_SMALL_BULLET_RIGHT;
			this->vx = 0.25;
			this->vy = 0;
			bulletwidth = 8;
			bulletheight = 6;
		}
		if (direction == 2) {
			state = SOPHIA_SMALL_BULLET_LEFT;
			this->vx = -0.25;
			this->vy = 0;
			bulletwidth = 8;
			bulletheight = 6;
		}
		if (direction == 3) {
			state = SOPHIA_SMALL_BULLET_UP;
			this->vx = 0;
			this->vy = -0.25;
			bulletwidth = 6;
			bulletheight = 8;
		}
	}
	if (type == 3) {
		this->bullettype = 3;
		if (direction == 1) {
			minenemyx = 1000, minenemyy = 100;
			state = SOPHIA_SMALL_ROCKET_RIGHT;
			this->vx = 0.15;
			this->vy = 0;
		}
		if (direction == 2) {
			state = SOPHIA_SMALL_ROCKET_LEFT;
			minenemyx = -1000, minenemyy = 100;
			this->vx = -0.15;
			this->vy = 0;
		}
		if (direction == 3) {
			minenemyx = 100, minenemyy = 1000;
			state = SOPHIA_SMALL_ROCKET_TOP;
			this->vx = 0;
			this->vy = -0.15;
		}
		bulletwidth = 11;
		bulletheight = 11;
	}
	if (type == 4) {
		this->bullettype = 4;
		TurningTime2->start();
		if (direction == 1) {
			bulletdirection = 1;
			state = SOPHIA_SMALL_ROCKET_RIGHT;
			this->vx = 0.15;
			this->vy = 0;
		}
		if (direction == 2) {
			state = SOPHIA_SMALL_ROCKET_LEFT;
			bulletdirection = 2;
			this->vx = -0.15;
			this->vy = 0;
		}
		if (direction == 3) {
			bulletdirection = 1;
			state = SOPHIA_SMALL_ROCKET_TOP;
			this->vx = -0.02;
			this->vy = -0.15;
		}
		if (direction == 4) {
			bulletdirection = 1;
			state = SOPHIA_SMALL_ROCKET_DOWN;
			this->vx = -0.02;
			this->vy = 0.15;
		}
		if (direction == 5) {
			bulletdirection =2;
			state = SOPHIA_SMALL_ROCKET_TOP;
			this->vx = 0.02;
			this->vy = -0.15;
		}
		if (direction == 6) {
			bulletdirection = 2;
			state = SOPHIA_SMALL_ROCKET_DOWN;
			this->vx = 0.02;
			this->vy = 0.15;
		}
		bulletwidth = 11;
		bulletheight = 11;
	}
	BulletManager::getinstance()->addBullet(this);
}
void PLayerBullet::render()
{

	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void PLayerBullet::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{


	GameObject::update(dt);
	short timestate = surviveTime->update(dt);
	short timestate2 = exploTime->update(dt);
	short timestate3 = TurningTime->update(dt);
	short timestate4 = TurningTime2->update(dt);
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
		for (UINT i = 0; i < coEvents.size(); i++) {

			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<Enemy*>(e->obj)) {
				if (e->ny != 0 || e->nx != 0) {
					dynamic_cast<Enemy*>(e->obj)->GetHit(1);
					surviveTime->stop(); timestate = TIMER_ENDED;
					active = -1;
					break;
				}
			}
		}
		if (bullettype < 3) {
			if (coEventsResult.size() != 0) {
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0 || nx != 0) {
						surviveTime->stop(); timestate = TIMER_ENDED;
						active = -1;
						break;
					}
				}
			}
		}
		y += dy;
		x += dx;
	}

	// rocket logic 

	if (bullettype == 3 && active == 1) {
		if (timestate3 == TIMER_INACTIVE) TurningTime->restart();
		else if (timestate3 == TIMER_ENDED) {
			int Tempdirection = 1;
			for (UINT i = 0; i < coObjects->size(); i++) {
				if (dynamic_cast<Enemy*>(coObjects->at(i)))
				{
					float temppx, temppy;
					Enemy* b = dynamic_cast<Enemy*>(coObjects->at(i));
					b->getPos(temppx, temppy);
					temppx = temppx - this->x;
					temppy = temppy - this->y;
					if ((temppx * temppx + temppy * temppy) < (minenemyx * minenemyx + minenemyy * minenemyy)) {
						minenemyx = temppx;
						minenemyy = temppy;
					}
				}
			}
			if (abs(minenemyx) > abs(minenemyy)) {
				if (minenemyx > 0) {
					this->vx = 0.15;
					this->vy = 0;
					state = SOPHIA_SMALL_ROCKET_RIGHT;
				}
				else
				{
					this->vx = -0.15;
					this->vy = 0;
					state = SOPHIA_SMALL_ROCKET_LEFT;
				}
			}
			else
			{
				if (minenemyy > 0) {
					this->vx = 0;
					this->vy = 0.15;
					state = SOPHIA_SMALL_ROCKET_DOWN;
				}
				else
				{
					this->vx = 0;
					this->vy = -0.15;
					state = SOPHIA_SMALL_ROCKET_TOP;
				}
			}
		}
	}
	if (bullettype == 4 && active == 1) {
		if (timestate4 == TIMER_ENDED) {
			if (bulletdirection == 1) {
				state = SOPHIA_SMALL_ROCKET_RIGHT;
				this->vx = 0.25;
				this->vy = 0;
			}
			else if (bulletdirection == 2) {
				state = SOPHIA_SMALL_ROCKET_LEFT;
				this->vx = -0.25;
				this->vy = 0;
			}
		}
	}


	if (timestate == TIMER_INACTIVE) surviveTime->restart();
	else if (timestate == TIMER_ENDED) {
		state = BULLET_EXPLO;

		if (vx > 0) { vx += 20; vy += 2; }
		if (vx < 0) { vx -= 20; vy += 2; }
		if (vy > 0) { vx += 2; vy += 20; }
		vx = 0;
		vy = 0;

		exploTime->restart();
	}
	if (timestate2 == TIMER_ENDED)
		BulletManager::getinstance()->removeBullet(this);
}

void PLayerBullet::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + bulletheight;
	right = left + bulletwidth;
}
PLayerBullet::~PLayerBullet()
{
}