#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float x, float y, float inputx, float inputy, int type) : Bullet(x, y, vx, vy) {

	this->HitPoint = 0;
	surviveTime = new GameTimer(2000);
	exploTime = new GameTimer(200);
	float tempc = sqrt(inputx * inputx + inputy * inputy);
	if (type == 1) {
		state = ENEMY_BULLET_1;
		this->vx = 0.1 * inputx / tempc;
		this->vy = 0.1 * inputy / tempc;
		bulletwidth = 6;
		bulletheight = 6;
		enemytype = 1;
	}
	if (type == 2) {
		state = ENEMY_BULLET_2;
		this->vx = inputx;
		this->vy = 0;
		bulletwidth = 10;
		bulletheight = 10;
		enemytype = 2;
	}
	if (type == 3) {
		state = ENEMY_BULLET_3;
		this->vx = inputx;
		this->vy = -0.3;
		bulletwidth = 8;
		bulletheight = 8;
		enemytype = 3;
		surviveTime = new GameTimer(500);
	}
	//if (type == 3) {
	//	state = SOPHIA_BULLET_UP;
	//	this->vx = 0;
	//	this->vy = -0.25;
	//	bulletwidth = 8;
	//	bulletheight = 26;
	//}
	BulletManager::getinstance()->addBullet(this);
}

void EnemyBullet::render()
{

	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void EnemyBullet::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (enemytype == 2) {
		vy += 0.03;
	}
	if (enemytype == 3)
	{
		vy += 0.03;
	}
	GameObject::update(dt);
	short timestate = surviveTime->update(dt);
	short timestate2 = exploTime->update(dt);

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
		if (enemytype == 1) {
			for (UINT i = 0; i < coEvents.size(); i++) {

				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<Player*>(e->obj)) {
					if (e->ny != 0 || e->nx != 0) {
						dynamic_cast<Player*>(e->obj)->PlayerGetHit(1);
						surviveTime->stop(); timestate = TIMER_ENDED;
						active = -1;
						break;
					}
				}
			}
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
			else {
				y += dy;
				x += dx;
			}
		}
		else if (enemytype == 2) {
			for (UINT i = 0; i < coEvents.size(); i++) {

				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<Player*>(e->obj)) {
					if (e->ny != 0 || e->nx != 0) {
						dynamic_cast<Player*>(e->obj)->PlayerGetHit(1);
						surviveTime->stop(); timestate = TIMER_ENDED;
						active = -1;
						break;
					}
				}
			}
			if (coEventsResult.size() != 0) {
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (ny < 0) {
						if (vy < 0.1) {
							vy = 0;
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
			else {
				y += dy;
				x += dx;
			}
		}
		else if (enemytype == 3) {
			for (UINT i = 0; i < coEvents.size(); i++) {

				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<Player*>(e->obj)) {
					if (e->ny != 0 || e->nx != 0) {
						dynamic_cast<Player*>(e->obj)->PlayerGetHit(1);
						surviveTime->stop(); timestate = TIMER_ENDED;
						active = -1;
						break;
					}
				}
			}
			if (coEventsResult.size() != 0) {
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (ny < 0) {
							vy = 0;
					}
					if (nx != 0) {
						vx = -vx;
					}
				}
			}
			else {
				y += dy;
				x += dx;
			}
		}
	}



	if (timestate == TIMER_INACTIVE) surviveTime->restart();
	else if (timestate == TIMER_ENDED) {
		state = BULLET_EXPLO;
		//if (vx > 0) { vx += 20; vy += 2; }
		//if (vx < 0) { vx -= 20; vy += 2; }
		//if (vx > 0) { vx += 2; vy += 20; }
		vx = 0;
		vy = 0;
		exploTime->restart();

	}
	if (timestate2 == TIMER_ENDED)
		BulletManager::getinstance()->removeBullet(this);
}

void EnemyBullet::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + bulletheight;
	right = left + bulletwidth;
}
EnemyBullet::~EnemyBullet()
{
}