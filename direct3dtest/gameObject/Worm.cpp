#include "Worm.h"

Worm::Worm(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->y -= 16;
	vx = 0.03;
	vy = 0.03;
	state = WORM_IDLE_LEFT;
	spawnPlace = 1;
}

void Worm::render()
{
	Enemy::render();
}

void Worm::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (!SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_WORM_MOVING))
		SoundManager::getInstance()->Play(eSoundId::SOUND_WORM_MOVING);
	Enemy::update(dt, coObjects);

	//x += vx * dt;
	//y += vy * dt;
	vy += 0.02;

	if (this->isDie == 2) {
		if (SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_WORM_MOVING)) {
			SoundManager::getInstance()->Stop(eSoundId::SOUND_WORM_MOVING);

		}
		this->isDie = 1;
	}
	////bounding logic
	//if (x <= 0) vx = 0.03;
	//else if (x >= SCREEN_WIDTH - 18) vx = -0.03;
	GameObject::update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {
		x += dx;
		y += dy;
		isOnAir = true;
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			 if (dynamic_cast<Block*>(e->obj)) {
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
				if (ny != 0) vy = 0;
				if (ny < 0) { isOnAir = false; }
				if (nx != 0) { vx = 0; vy -= 0.06; }
			}
		}
		x += dx;
		y += dy;
	}

	//if (nx != 0 && !ignoreCollision) vx = 0;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Player*>(coObjects->at(i)))
		{
			float px, py;
			Player* p = dynamic_cast<Player*>(coObjects->at(i));
			p->getPos(px, py);
			if (this->x > px)vx = -0.03;
			else vx = 0.03;
			break;
		}
	}

	if (vx > 0) {
		state = WORM_MOVE_RIGHT;
	}
	else if (vx < 0) {
		state = WORM_MOVE_LEFT;
	}
	else {
		if (state == WORM_MOVE_LEFT) state = WORM_IDLE_LEFT;
		else if (state == WORM_MOVE_RIGHT) state = WORM_IDLE_RIGHT;
	}
}
void Worm::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_WORM_HEIGHT;
	right = left + BBOX_WORM_WIDTH;
}

Worm::~Worm()
{
}
