
#include "Sophia.h"

Sophia::Sophia(float x, float y, int hp) : Player(x, y, hp)
{
	vx = 0; vy = 0;
	nx = 1;
	state = SOPHIA_BODY_FLAT_IDLE_RIGHT;
	movingState = SOPHIA_WHEEL_NORMAL_RIGHT_IDLE;
}

void Sophia::render()
{
	LPANIMATION body_ani;
	LPANIMATION wheel_ani;
	body_ani = AnimationManager::getInstance()->get(state);
	wheel_ani = AnimationManager::getInstance()->get(movingState);
	body_ani->render(x - 1, y - 2);
	wheel_ani->render(x, y + 8);
}

void Sophia::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

	if (forceControlState != IDLE) {
		controlState = forceControlState;
	}
	if (controlState & (LEFT | RIGHT)) {
		if ((controlState & (LEFT)) && (!(controlState & (RIGHT)))) {
			if (vx >= -SOPHIA_MOVE_SPEED_CAP)
				vx -= SOPHIA_MOVE_ACCEL;
			else vx == -SOPHIA_MOVE_SPEED_CAP;
		}
		else if (controlState & (RIGHT) && (!(controlState & (LEFT)))) {
			if (vx <= SOPHIA_MOVE_SPEED_CAP)
				vx += SOPHIA_MOVE_ACCEL;
			else vx == SOPHIA_MOVE_SPEED_CAP;
		}
		else {
			if (vx > 0.011) vx -= SOPHIA_MOVE_ACCEL;
			else if (vx < -0.011) vx += SOPHIA_MOVE_ACCEL;
			else vx = 0;
		}
	}
	else {
		if (vx > 0.011) vx -= SOPHIA_MOVE_ACCEL;
		else if (vx < -0.011) vx += SOPHIA_MOVE_ACCEL;
		else vx = 0;
	}

	if (controlState & (PRIMARY)) {
		if (!isOnAir) {
			vy -= SOPHIA_JUMP_SPEED;
			isOnAir = true;
		}
	}
	else {
		if (vy < 0) vy = 0;
	}
	vy += 0.01;

	//change animation state based on final vx and vy
	if (vx > 0.001) {
		changeState(SOPHIA_BODY_FLAT_MOVE_RIGHT);
		changeMovingState(SOPHIA_WHEEL_NORMAL_RIGHT);
	}
	else if (vx < -0.001) {
		changeState(SOPHIA_BODY_FLAT_MOVE_LEFT);
		changeMovingState(SOPHIA_WHEEL_NORMAL_LEFT);
	}
	else {
		changeState(COMMON_SOPHIA_IDLE);
		changeMovingState(SOPHIA_MOVING_IDLE);
	}

	
	if (controlState & UP) {
		changeState(SOPHIA_GUN_MOUNT_RAISE);
	}
	
	GameObject::update(dt);

	//Handling collision

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
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back player if collides with a moving objects, what if player is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		if (!ignoreCollision) x += min_tx * dx + nx * 0.4f;
		else x += dx;
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Portal*>(e->obj))
			{
				Portal* p = dynamic_cast<Portal*>(e->obj);
				if (!ignoreCollision) this->activeSection = p->getSectionEnd();
			}
		}

		//float t, l, b, r;
		//coEvents[0]->obj->GetBoundingBox(t, l, b, r);
		//std::string s1 = std::to_string(t);
		//std::string s2 = std::to_string(l);
		//DebugOut(s1.c_str());
		//DebugOut("\n");
		//DebugOut(s2.c_str());
		//DebugOut("\n\n");
		
		
		if (ny != 0) vy = 0;
		if (ny < 0) { isOnAir = false; }
		if (nx != 0 && !ignoreCollision) vx = 0;
	}
}

Sophia::~Sophia()
{
}

void Sophia::changeState(int stateId)
{
	if (stateId == COMMON_SOPHIA_IDLE) {
		if (state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_SLANT_LEFT || state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_FLAT_IDLE_LEFT)
			stateId = SOPHIA_BODY_FLAT_IDLE_LEFT;
		else if (state == SOPHIA_BODY_FLAT_MOVE_RIGHT || state == SOPHIA_BODY_SLANT_RIGHT || state == SOPHIA_BODY_UP_RIGHT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT)
			stateId = SOPHIA_BODY_FLAT_IDLE_RIGHT;
		else stateId = SOPHIA_BODY_FLAT_IDLE_RIGHT;
	}
	if (stateId == SOPHIA_GUN_MOUNT_RAISE) {
		if (state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_SLANT_LEFT || state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_FLAT_IDLE_LEFT)
			stateId = SOPHIA_BODY_UP_LEFT;
		else if (state == SOPHIA_BODY_FLAT_MOVE_RIGHT || state == SOPHIA_BODY_SLANT_RIGHT || state == SOPHIA_BODY_UP_RIGHT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT)
			stateId = SOPHIA_BODY_UP_RIGHT;
		else stateId = SOPHIA_BODY_FLAT_IDLE_RIGHT;
	}
	switch (stateId) {
	case SOPHIA_BODY_FLAT_IDLE_LEFT : case SOPHIA_BODY_FLAT_MOVE_LEFT:
		if (state == SOPHIA_BODY_FLAT_MOVE_RIGHT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT)
			state = SOPHIA_BODY_TURN_TO_RIGHT;
		else if (state == SOPHIA_BODY_TURN_TO_RIGHT)
			state = SOPHIA_BODY_TURN_TO_LEFT;
		else if (state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_UP_RIGHT)
			state = SOPHIA_BODY_SLANT_LEFT;
		else state = stateId;
		break;
	case SOPHIA_BODY_FLAT_IDLE_RIGHT: case SOPHIA_BODY_FLAT_MOVE_RIGHT:
		if (state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_FLAT_IDLE_LEFT)
			state = SOPHIA_BODY_TURN_TO_LEFT;
		else if (state == SOPHIA_BODY_TURN_TO_LEFT)
			state = SOPHIA_BODY_TURN_TO_RIGHT;
		else if (state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_UP_RIGHT)
			state = SOPHIA_BODY_SLANT_RIGHT;
		else state = stateId;
		break;
	case SOPHIA_BODY_UP_LEFT:
		if (state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_FLAT_IDLE_LEFT)
			state = SOPHIA_BODY_SLANT_LEFT;
		else if (state == SOPHIA_BODY_SLANT_LEFT)
			state = SOPHIA_BODY_UP_LEFT;
		break;
	case SOPHIA_BODY_UP_RIGHT:
		if (state == SOPHIA_BODY_FLAT_MOVE_RIGHT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT)
			state = SOPHIA_BODY_SLANT_RIGHT;
		else if (state == SOPHIA_BODY_SLANT_RIGHT)
			state = SOPHIA_BODY_UP_RIGHT;
		break;
	default:
		state = stateId;
	}
}

void Sophia::changeMovingState(int stateId)
{
	switch (stateId) {
	case SOPHIA_MOVING_IDLE:
		if (movingState == SOPHIA_WHEEL_NORMAL_LEFT)
			movingState = SOPHIA_WHEEL_NORMAL_LEFT_IDLE;
		if (movingState == SOPHIA_WHEEL_NORMAL_RIGHT)
			movingState = SOPHIA_WHEEL_NORMAL_RIGHT_IDLE;
		break;
	default:
		movingState = stateId;
	}
}

//NOTE: Turn to pure virtual ASAP after inheiritance is completed
void Sophia::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_SOPHIA_HEIGHT;
	right = left + BBOX_SOPHIA_WIDTH;
}