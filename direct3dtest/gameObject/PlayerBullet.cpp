#include "PlayerBullet.h"
PLayerBullet::PLayerBullet(float x, float y, float vx, float vy,int type,int direction) : Bullet(x,y,vx,vy) {

	this->HitPoint = 5;
	surviveTime = new GameTimer(2000);
	exploTime = new GameTimer(200);
	TurningTime = new GameTimer(100);
	TurningTime2 = new GameTimer(200);
	velocity = 0.05;
	if (type == 1) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_FIRING);
		this->bullettype = 1;
		if (direction == 1) {
			state = SOPHIA_BULLET_RIGHT;
			this->vx = 0.25;
			this->vy = 0;
			bulletwidth = 26;
			bulletheight = 6;
		}
		if (direction == 2) {
			state = SOPHIA_BULLET_LEFT;
			this->vx = -0.25;
			this->vy = 0;
			bulletwidth = 26;
			bulletheight = 6;
		}
		if (direction == 3) {
			state = SOPHIA_BULLET_UP;
			this->vx = 0;
			this->vy = -0.25;
			bulletwidth = 6;
			bulletheight = 26;
		}
	}
	if (type == 2)
	{
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_FIRING);
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
		if (direction == 4) {
			state = SOPHIA_SMALL_BULLET_DOWN;
			this->vx = 0;
			this->vy = 0.25;
			bulletwidth = 6;
			bulletheight = 8;
		}
	}
	if (type == 3) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_SOPHIA_FIRING);
		this->bullettype = 3;
		if (direction == 1) {
			minenemyx = 1000, minenemyy = 100;
			state = SOPHIA_SMALL_ROCKET_RIGHT;
			this->vx = velocity;
			this->vy = 0;
		}
		if (direction == 2) {
			state = SOPHIA_SMALL_ROCKET_LEFT;
			minenemyx = -1000, minenemyy = 100;
			this->vx = -velocity;
			this->vy = 0;
		}
		if (direction == 3) {
			minenemyx = 100, minenemyy = 1000;
			state = SOPHIA_SMALL_ROCKET_TOP;
			this->vx = 0;
			this->vy = -velocity;
		}
		bulletwidth = 11;
		bulletheight = 11;
	}
	if (type == 4) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_SOPHIA_FIRING);
		this->bullettype = 4;
		TurningTime2->start();
		if (direction == 1) {
			bulletdirection = 1;
			state = SOPHIA_SMALL_ROCKET_RIGHT;
			this->vx = 0.2;
			this->vy = 0;
		}
		if (direction == 2) {
			state = SOPHIA_SMALL_ROCKET_LEFT;
			bulletdirection = 2;
			this->vx = -0.2;
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
	if(type ==5){
		SoundManager::getInstance()->Play(eSoundId::SOUND_SMALLJASON_FIRING);
		state = JASON_BULLET;
		this->vx = vx;
		this->vy = vy;
		bulletwidth = 4;
		bulletheight = 4;
	}
	if (type == 6) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_FIRING);
		this->bullettype = 6;
		bulletdirection = direction;
		state = SOPHIA_SMALL_BULLET_LEFT;
		bulletwidth = 8;
		bulletheight = 8;
		this->y += 10;
		this->vx = vx;
		this->vy = vy;
	}

	BulletManager::getinstance()->addBullet(this);
}
PLayerBullet::PLayerBullet(float x, float y, float vx, float vy, int type, int direction, int value) : Bullet(x, y, vx, vy) 
{
	bulletdirection = direction;
	int bulletvalue = value;
	bulletwidth = 8;
	bulletheight = 8;
	surviveTime = new GameTimer(1000);
	exploTime = new GameTimer(200);
	TurningTime = new GameTimer(100);
	TurningTime2 = new GameTimer(200);
	if (value <= 1) {
		this->bullettype = 2;
		surviveTime = new GameTimer(1500);
		this->HitPoint = 3;
	}
	else if (value >= 2 && value <= 4) {
		this->bullettype = 2;
		surviveTime = new GameTimer(4000);
		this->HitPoint = 4;
	}
	else if (value > 4) {
		this->bullettype = 6;
		surviveTime = new GameTimer(5000);
		this->HitPoint = 5;
	}
	if (bullettype == 2)
	{
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_FIRING);
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
		if (direction == 4) {
			state = SOPHIA_SMALL_BULLET_DOWN;
			this->vx = 0;
			this->vy = 0.25;
			bulletwidth = 6;
			bulletheight = 8;
		}
	}
	else if (bullettype == 6) {
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_FIRING);
		this->bullettype = 6;
		state = CIRCLE_BULLET;
		this->y += 10;
		this->vx = vx;
		this->vy = vy;
	}
	velocity = 0.05;

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
	velocity += 0.01;
	if (this->HitPoint > 16) this->HitPoint = 16;
	 GameObject::update(dt);
	 if (bullettype == 6 && surviveTime->peekState() != TIMER_ENDED) {
		 getDxDy(this->dx, this->dy, dt, T);
	 }

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
					dynamic_cast<Enemy*>(e->obj)->GetHit(HitPoint);
					if (this->bullettype == 1 || this->bullettype == 2)
						BulletManager::getinstance()->removeBullet(this);
					surviveTime->stop(); timestate = TIMER_ENDED;
					active = -1;
					break;
				}
			}

		}
		if (bullettype < 3 || bullettype == 6) {
			if (coEventsResult.size() != 0) {
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<Block*>(e->obj)) {
					/*	x += min_tx * dx + nx * 0.4f;
						y += min_ty * dy + ny * 0.4f;*/
						if (ny != 0 || nx != 0) {
							dynamic_cast<Block*>(e->obj)->getHitByBullet();
							surviveTime->stop(); timestate = TIMER_ENDED;
							active = -1;
							break;
						}
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
					this->vx = velocity;
					this->vy = 0;
					state = SOPHIA_SMALL_ROCKET_RIGHT;
				}
				else
				{
					this->vx = -velocity;
					this->vy = 0;
					state = SOPHIA_SMALL_ROCKET_LEFT;
				}
			}
			else
			{
				if (minenemyy > 0) {
					this->vx = 0;
					this->vy = velocity;
					state = SOPHIA_SMALL_ROCKET_DOWN;
				}
				else
				{
					this->vx = 0;
					this->vy = -velocity;
					state = SOPHIA_SMALL_ROCKET_TOP;
				}
			}
		}
	}
	if (bullettype == 4 && active == 1) {
		if (timestate4 == TIMER_ENDED) {
			if (bulletdirection == 1) {
				state = SOPHIA_SMALL_ROCKET_RIGHT;
				this->vx = velocity;
				this->vy = 0;
			}
			else if (bulletdirection == 2) {
				state = SOPHIA_SMALL_ROCKET_LEFT;
				this->vx = -velocity;
				this->vy = 0;
			}
		}
	}


	if (timestate == TIMER_INACTIVE) surviveTime->restart();
	else if (timestate == TIMER_ENDED) {
		state = BULLET_EXPLO;
		SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_BULLET_EXPLODE);
		if (vx > 0) { vx += 20; vy += 2; }
		if (vx < 0) { vx -= 20; vy += 2; }
		if (vy > 0) { vx += 2; vy += 20; }
		if (vy < 0) { vx += 2; vy -= 20; }
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
#define bankinh 32
#define pi 3.14159265359
#define vantoc 0.3
void PLayerBullet::getDxDy(float& dx, float& dy, DWORD dt, DWORD& Totaltime) {
	float T = 2 * pi * 32 / vantoc;
	float omega = 2 * pi / T;
	dy += bankinh * cos(omega * (Totaltime + dt)) - bankinh * cos(omega * (Totaltime));
	dx += bankinh * sin(omega * (Totaltime + dt)) - bankinh * sin(omega * Totaltime);
	Totaltime += dt;
};