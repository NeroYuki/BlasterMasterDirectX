#include "Jumper.h"
Jumper::Jumper(float x, float y, int hp) :Enemy(x,y,hp)
{
	vx = 0.00;
	vy = 0.00;
	state = JUMPER_IDLE_RIGHT;
	waitTime = new GameTimer(100);
	watTime2= new GameTimer(5000);
	isJump = false;
	facing = 1;
}

void Jumper::render()
{
	Enemy::render();
}

void Jumper::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt, coObjects);
	if (this->isDie == 2) this->isDie = 1;
	vy += 0.05;
	int futureCollision = -1;
	////bounding logic
	//if (x <= 0) vx = 0.03;
	//else if (x >= SCREEN_WIDTH - 18) vx = -0.03;
	GameObject::update(dt);
	short timerstate = waitTime->update(dt);
	short timerstate2 = watTime2->update(dt);
	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (vx < 0) {
		CalcPotentialCollisions(coObjects, coEvents, -16, 0);
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;
		if (coEvents.size() == 0) {
			futureCollision = 0;
		}
		else futureCollision = 1;
	}
	else if (vx > 0) {
		CalcPotentialCollisions(coObjects, coEvents, 16, 0);
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;
		if (coEvents.size() == 0) {
			futureCollision = 0;
		}
		else futureCollision = 1;
	}
	coEvents.clear();
	coEventsResult.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
		isJump = true;
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
					if (ny != 0) { vy = 0; };
					if (ny < 0) {
						isJump = false;
						if (jumpCounter != 0) vx = 0;
						else if (futureCollision == 0) {
							vx = -vx; facing2 = -facing2;
						}
					}
					if (nx > 0) {
						vx = 0.05;
						facing2 = -facing2;
					}
					if (nx < 0) {
						vx = -0.05;
						facing2 = -facing2;
					}
				}
			}
		}
		else {
			y += dy;
			x += dx;
			isJump = true;
		}
	}

	
	//if (nx != 0 && !ignoreCollision) vx = 0;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Player*>(coObjects->at(i)))
		{
			float px, py;
			Player* p = dynamic_cast<Player*>(coObjects->at(i));
			p->getPos(px, py);
			if (this->x > px)facing = 1;
			else if (this->x < px)facing = 2;
		}

		//if (dynamic_cast<Bullet*>(coObjects->at(i))) 
		//{
		//	float px, py;
		//	float top, left, bottom, right;
		//	Bullet* b = dynamic_cast<Bullet*>(coObjects->at(i));
		//	b->getPos(px, py);
		//	this->GetBoundingBox(top, left, bottom, right);
		//	if (px<right && px> left && py > top && py < bottom) {
		//		this->isDie = 1;
		//		break;
		//	}
		//}
	}
	
	if (jumpCounter > 0) {
		if (!isJump) {
			if (timerstate == TIMER_INACTIVE) waitTime->restart();
			else if (timerstate == TIMER_ENDED) {
				if (facing == 1) {
					vy = -0.3;
					vx = -0.05;
					isJump == true;
					facing2 = 1;
				}
				else {
					vy = -0.3;
					vx = 0.05;
					isJump == true;
					facing2 == -1;
				}
				jumpCounter--;
			}

		}
	}
	else {
		if (timerstate2 == TIMER_INACTIVE) watTime2->restart();
		else if (timerstate2 == TIMER_ENDED) {
			jumpCounter = 3;
			if (facing2 == 1) {
				vx = -0.1;
			}
			else {
				vx = 0.1;
			}
		}
	}


	if (vx < 0) {
		state = JUMPER_MOVE_LEFT;
	}
	else if (vx > 0) {
		state = JUMPER_MOVE_RIGHT;
	}
}

void Jumper::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_JUMPER_HEIGHT;
	right = left + BBOX_JUMPER_WIDTH;
}

Jumper::~Jumper()
{
}
