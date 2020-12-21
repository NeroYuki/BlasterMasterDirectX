#include "PlayerBullet.h"
PLayerBullet::PLayerBullet(float x, float y, float vx, float vy,int type) : Bullet(x,y,vx,vy) {

	this->HitPoint = 0;
	surviveTime = new GameTimer(2000);
	exploTime = new GameTimer(200);
	if (type == 1) { 
		state = SOPHIA_BULLET_RIGHT;
		this->vx = 0.25;
		this->vy = 0;
		bulletwidth = 26;
		bulletheight = 8;
	}
	if (type == 2) {
		state = SOPHIA_BULLET_LEFT; 
		this->vx = -0.25;
		this->vy = 0;
		bulletwidth = 26;
		bulletheight = 8;
	}
	if (type == 3) { 
		state = SOPHIA_BULLET_UP;
		this->vx = 0;
		this->vy = -0.25;
		bulletwidth = 8;
		bulletheight = 26;
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
	//x += dx;
	//y += dy;
	//if (active == 1) {
	//	for (UINT i = 0; i < coObjects->size(); i++) {
	//		if (dynamic_cast<Enemy*>(coObjects->at(i)))
	//		{
	//			float px, py;
	//			float top, left, bottom, right;
	//			Enemy* b = dynamic_cast<Enemy*>(coObjects->at(i));
	//			this->getPos(px, py);
	//			b->GetBoundingBox(top, left, bottom, right);
	//			if (px + 26 < right && px + 26 > left && py + 4 > top && py + 4 < bottom) {
	//				b->GetHit(2);
	//				surviveTime->stop(); timestate = TIMER_ENDED;
	//				active = -1;
	//				break;
	//			}
	//		}
	//		if (dynamic_cast<Block*>(coObjects->at(i)))
	//		{
	//			float px, py;
	//			float top, left, bottom, right;
	//			Block* b = dynamic_cast<Block*>(coObjects->at(i));
	//			this->getPos(px, py);
	//			b->GetBoundingBox(top, left, bottom, right);
	//			if (px + 26 < right && px + 26 > left && py + 4 > top && py + 4 < bottom) {
	//				surviveTime->stop(); timestate = TIMER_ENDED;
	//				active = -1;
	//				break;
	//			}
	//		}
	//	}
	//}
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
	if(timestate2 == TIMER_ENDED)
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