#include "JasonTop.h"

JasonTop::JasonTop(float x, float y, int hp) : Player(x, y, hp)
{
	facing = 1;
	vx = 0; vy = 0;
	state = TOP_JASON_IDLE_LEFT;
	bulletDelayTimer = new GameTimer(200);
	grenadeDelayTimer = new GameTimer(300);
	deadState = 10009;
	inDeadAniTimer = new GameTimer(1600);
}

void JasonTop::render()
{
	LPANIMATION ani;
	LPANIMATION dead_ani;
	dead_ani = AnimationManager::getInstance()->get(deadState);
	ani = AnimationManager::getInstance()->get(state);
	if (this->invincible == 1) {
		dead_ani->render(x, y );
	}
	else {
		ani = AnimationManager::getInstance()->get(state);
		if (istakingdmg == 1)ani->render(x, y, D3DCOLOR_RGBA(228, 128, 125, 255));
		else ani->render(x, y);
	}
}
void JasonTop::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Player::update(dt, coObjects);
	vx = 0; vy = 0;
	
	if (forceControlState != IDLE) { 
		controlState = forceControlState; 
	}
	if (controlState & (DOWN)) {
		vy += PLAYER_WALKING_SPEED;
		this->changeState(TOP_JASON_WALK_DOWN);
		facing = 4;
	}
	if (controlState & (UP)) {
		vy -= PLAYER_WALKING_SPEED;
		this->changeState(TOP_JASON_WALK_UP);
		facing = 3;
	}
	if (controlState & (LEFT)) {
		vx -= PLAYER_WALKING_SPEED;
		this->changeState(TOP_JASON_WALK_LEFT);
		facing = 1;
	}
	if (controlState & (RIGHT)) {
		vx += PLAYER_WALKING_SPEED;
		this->changeState(TOP_JASON_WALK_RIGHT);
		facing = 2;
	}

	if (controlState == IDLE) {
		this->changeState(COMMON_PLAYER_IDLE);
	}

	if (controlState & (PRIMARY)) {
		if (grenadeDelayTimer->peekState() == TIMER_INACTIVE) {
			switch (facing) {
			case 1: new Grenade(this->x + 12, this->y + 16, -0.2, 0); break;
			case 2: new Grenade(this->x + 12, this->y + 16, 0.2, 0); break;
			case 3: new Grenade(this->x + 12, this->y + 16, 0, -0.2); break;
			case 4: new Grenade(this->x + 12, this->y + 16, 0, 0.2); break;
			default: break;
			}
			grenadeDelayTimer->restart();
		}
	}
	this->upgrade = SharedData::getInstance()->upgrade;
	bullettype = 6;
	if (controlState & (SECONDARY)) {
		if (bulletDelayTimer->peekState() == TIMER_INACTIVE) {
			switch (facing) {
			case 1: new PLayerBullet(this->x + 12, this->y + 16, -0.1, 0, bullettype, 2, upgrade); break;
			case 2: new PLayerBullet(this->x + 12, this->y + 16, 0.1, 0, bullettype, 1, upgrade); break;
			case 3:	new PLayerBullet(this->x + 12, this->y + 16, 0, -0.1, bullettype, 3, upgrade); break;
			case 4: new PLayerBullet(this->x + 12, this->y + 16, 0, 0.1, bullettype, 4, upgrade); break;
			default: break;
			}
			bulletDelayTimer->restart();
		}
	}
	//Change animation state logic here

	GameObject::update(dt);
	bulletDelayTimer->update(dt);
	grenadeDelayTimer->update(dt);
	//Handling collision
	if (this->ignoreCollision) {
		x += dx;
		y += dy;
		return;
	}

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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
			if (dynamic_cast<ScenePortal*>(e->obj)) {
				ScenePortal* portal = dynamic_cast<ScenePortal*>(e->obj);
				this->followingScenePortal = portal;
				int ischangescene = this->followingScenePortal->getIsChangeScene();
				if (ischangescene == 1) {
					this->changeSection = 1;
				}
			}
			else if (dynamic_cast<Collectable*>(e->obj)) {
				Collectable* pickup = dynamic_cast<Collectable*>(e->obj);
				int t, v;
				pickup->getPicked(t, v);
				if (t == 1) this->hitpoint += v;
				if (hitpoint > 16) hitpoint == 16;
				if (t == 2) this->upgrade += v;
				if (this->upgrade > 8) upgrade = 8;
			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				if(!dynamic_cast<Teleporter*>(e->obj))
				this->PlayerGetHit(2);
			}
			else if (dynamic_cast<Spike*>(e->obj))
			{
				Spike* spike = dynamic_cast<Spike*>(e->obj);
				this->contactedSpike = spike;
			}
		}
		if (coEventsResult.size() > 0) {
			if (!ignoreCollision) {
				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;
			}
			else {
				x += dx;
				y += dy;
			}			
			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{

				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Portal*>(e->obj))
				{
					Portal* p = dynamic_cast<Portal*>(e->obj);
					this->activeSection = p->getSectionEnd();
				}

			}
		}
		else {
			x += dx;
			y += dy;
		}
	}
}

JasonTop::~JasonTop()
{
}

void JasonTop::changeState(int stateId)
{
	switch (stateId) {
		//case COMMON_PLAYER_IDLE:
		//	state = stateId;
		//	break;
	case COMMON_PLAYER_IDLE:
		if (state == TOP_JASON_WALK_LEFT) state = TOP_JASON_IDLE_LEFT;
		else if (state == TOP_JASON_WALK_RIGHT) state = TOP_JASON_IDLE_RIGHT;
		else if (state == TOP_JASON_WALK_UP) state = TOP_JASON_IDLE_UP;
		else if (state == TOP_JASON_WALK_DOWN) state = TOP_JASON_IDLE_DOWN;
		else break;
		break;
	default:
		state = stateId;
	}
}

void JasonTop::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y + 19;
	left = this->x+5;
	bottom = top + BBOX_PLAYER_HEIGHT-2;
	right = left + BBOX_PLAYER_WIDTH-5;
}

