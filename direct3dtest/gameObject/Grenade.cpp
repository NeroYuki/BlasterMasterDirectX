#include "Grenade.h"

Grenade::Grenade(float x, float y, float vx, float vy) : Bullet(x, y, vx, vy)
{
	this->HitPoint = 0;
	surviveTime = new GameTimer(200);
	exploTime = new GameTimer(200);
	this->vx = vx;
	this->vy = vy;
	bulletwidth = 10;
	bulletheight = 10;
	this->state = GRENADE_STATE;
	active = 1;
	BulletManager::getinstance()->addBullet(this);
}

void Grenade::render()
{
	LPANIMATION ani;

	ani = AnimationManager::getInstance()->get(state);
		ani->render(x, y);
}

void Grenade::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::update(dt);
	short timestate = surviveTime->update(dt);
	short timestate2 = exploTime->update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0) {
		if(active ==1)
			x += dx;
			y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (active == 1) {
			if (coEventsResult.size() != 0) {

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					x += min_tx * dx + nx * 0.4f;
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0 || nx != 0) {
						surviveTime->stop(); timestate = TIMER_ENDED;
						break;
					}

				}
			}
			else {
				x += dx;
				y += dy;
			}
			
		}
	}
	if (active == -1) {
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<Enemy*>(coObjects->at(i)))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(coObjects->at(i));
				float a, b, c, d;
				enemy->GetBoundingBox(a, b, c, d);
				if (checkIfHit(a,b,c,d) == 1)
					enemy->GetHit(100);
			}
		}
		active = 0;
	}

	if (timestate == TIMER_INACTIVE) surviveTime->restart();
	else if (timestate == TIMER_ENDED) {
		state = GRENADE_EXPLOSION;
		if (active == 1) { 
			this->vx = 0;
			this->vy = 0;
			active = -1;
			exploTime->restart();
		}
	}
	if (timestate2 == TIMER_ENDED) {
		BulletManager::getinstance()->removeBullet(this);
	}


}
void Grenade::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + bulletheight;
	right = left + bulletwidth;
}

int Grenade::checkIfHit(float a, float b, float c, float d)
{
	float x1 = b, x2 = d, y1 = a, y2 = c;
	x1 = (x1 + x2) / 2;
	y1 = (y1 + y2) / 2;
	if ((x1>(this->x-20))&&(x1<(this->x+30))) {
		if ((y1 > (this->y - 20)) && (y1 < (this->y + 30))) {
			return 1;
		}
	}
	return 0;
}

Grenade::~Grenade()
{

}
