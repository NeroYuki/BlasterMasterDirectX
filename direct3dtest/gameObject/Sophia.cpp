
#include "Sophia.h"

Sophia::Sophia(float x, float y, int hp) : Player(x, y, hp)
{
	vx = 0; vy = 0;
	nx = 1;
	state = SOPHIA_BODY_FLAT_IDLE_RIGHT;
	movingState = SOPHIA_WHEEL_NORMAL_RIGHT_IDLE;
	turningTimer = new GameTimer(250);
	gunRaiseTimer = new GameTimer(100);
	bulletDelayTimer = new GameTimer(300);
	upgrade = 2;
	rocket = 5;
}

void Sophia::render()
{
	LPANIMATION body_ani;
	LPANIMATION wheel_ani;
	body_ani = AnimationManager::getInstance()->get(state);
	wheel_ani = AnimationManager::getInstance()->get(movingState);
	float body_render_x = x - 1;
	float body_render_y = y - 2;
	if (state == SOPHIA_BODY_SLANT_LEFT) {
		body_render_y -= 6; body_render_x += 2;
	}
	else if (state == SOPHIA_BODY_UP_LEFT) {
		body_render_y -= 16; body_render_x += 8;
	}
	else if (state == SOPHIA_BODY_SLANT_RIGHT) {
		body_render_y -= 6; body_render_x -= 0;
	}
	else if (state == SOPHIA_BODY_UP_RIGHT) {
		body_render_y -= 16; body_render_x -= 4;
	}
	if (isOnAir && dy < -1) body_render_y -= 4;
	body_ani->render(body_render_x, body_render_y);
	wheel_ani->render(x, y + 8);
}

void Sophia::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{

	if (forceControlState != IDLE) {
		controlState = forceControlState;
	}
	if (controlState & (LEFT | RIGHT)) {

		//NOTE: body state is controlled by input
		if ((controlState & (LEFT)) && (!(controlState & (RIGHT)))) {
			if (vx >= -SOPHIA_MOVE_SPEED_CAP)
				vx -= SOPHIA_MOVE_ACCEL;
			else vx == -SOPHIA_MOVE_SPEED_CAP;
			changeState(SOPHIA_BODY_FLAT_MOVE_LEFT);
			nx = -1;
		}
		else if (controlState & (RIGHT) && (!(controlState & (LEFT)))) {
			if (vx <= SOPHIA_MOVE_SPEED_CAP)
				vx += SOPHIA_MOVE_ACCEL;
			else vx == SOPHIA_MOVE_SPEED_CAP;
			changeState(SOPHIA_BODY_FLAT_MOVE_RIGHT);
			nx = 1;
		}
		else {
			if (vx > 0.011) vx -= SOPHIA_MOVE_ACCEL;
			else if (vx < -0.011) vx += SOPHIA_MOVE_ACCEL;
			else vx = 0;
			changeState(COMMON_SOPHIA_IDLE);
		}
	}
	else {
		if (vx > 0.011) vx -= SOPHIA_MOVE_ACCEL;
		else if (vx < -0.011) vx += SOPHIA_MOVE_ACCEL;
		else vx = 0;
		changeState(COMMON_SOPHIA_IDLE);
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
	this->rocket = 3;
	if (controlState & (SECONDARY) ) {
		if (bulletDelayTimer->peekState() == TIMER_INACTIVE) {
			if (controlState & (DOWN)){
				if (nx == 1) {
					if (rocket == 3) {
						new PLayerBullet(this->x + BBOX_SOPHIA_WIDTH - 10, this->y + 1, 0, 0, 3, 1);
					}
					else if (rocket == 4) {
						new PLayerBullet(this->x + BBOX_SOPHIA_WIDTH - 10, this->y + 1, 0, 0, 4, 1);
						new PLayerBullet(this->x + BBOX_SOPHIA_WIDTH - 10, this->y + 1, 0, 0, 4, 3);
						new PLayerBullet(this->x + BBOX_SOPHIA_WIDTH - 10, this->y + 1, 0, 0, 4, 4);
					}
					else if (rocket == 5) {
						new lightning(this->x + 5, this->y + BBOX_SOPHIA_HEIGHT);
					}
				}
				else if (nx == -1) {
					if (rocket == 3) {
						new PLayerBullet(this->x - 5, this->y + 1, 0, 0, 3, 2);
					}
					else if (rocket == 4) {
						new PLayerBullet(this->x - 5, this->y + 1, 0, 0, 4, 2);
						new PLayerBullet(this->x - 5, this->y + 1, 0, 0, 4, 5);
						new PLayerBullet(this->x - 5, this->y + 1, 0, 0, 4, 6);
					}
					else if (rocket == 5) {
						new lightning(this->x + 5, this->y + BBOX_SOPHIA_HEIGHT);
					}
				}
			}
			else {
				if (ny == 1)
				{
					if (nx == 1)
						new PLayerBullet(this->x + 5, this->y - 26, 0, 0, upgrade, 3);
					else if (nx == -1)
						new PLayerBullet(this->x + 12, this->y - 26, 0, 0, upgrade, 3);

				}
				else if (nx == 1) {
					new PLayerBullet(this->x + BBOX_SOPHIA_WIDTH - 10, this->y + 1, 0, 0, upgrade, 1);
				}
				else if (nx == -1) {
					new PLayerBullet(this->x - 5, this->y + 1, 0, 0, upgrade, 2);
				}
			}
			bulletDelayTimer->restart();
		}
	}

	
	if (controlState & UP) {
		changeState(SOPHIA_GUN_MOUNT_RAISE);
		ny = 1;
	}
	else {
		changeState(SOPHIA_GUN_MOUNT_UNRAISE);
		ny = 0;
	}

	//NOTE: Wheel state is control by actual movement
	if (vx > 0.001) {

		changeMovingState(SOPHIA_MOVING_RIGHT);
	}
	else if (vx < -0.001) {
		changeMovingState(SOPHIA_MOVING_LEFT);
	}
	else {
		changeMovingState(SOPHIA_MOVING_IDLE);
	}
	
	GameObject::update(dt);
	turningTimer->update(dt);
	gunRaiseTimer->update(dt);
	bulletDelayTimer->update(dt);
	//Handling collision

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
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		FilterCollisionBlock(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//after this method, coEvents SHOULD only contain collision event thats the target is not a block (ie Entity) 
		//and coEventsResult is now contain closest collision to a block to adjust player position accordingly
		if (coEventsResult.size() != 0) {
			if (!ignoreCollision) x += min_tx * dx + nx * 0.4f;
			else x += dx;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0) vx = 0;
			if (ny < 0) { isOnAir = false; }
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++) {
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Portal*>(e->obj))
				{
					Portal* p = dynamic_cast<Portal*>(e->obj);
					if (!ignoreCollision) this->activeSection = p->getSectionEnd();
				}
			}
		}
		else {
			y += dy;
			x += dx;
		}

		for (UINT i = 0; i < coEvents.size(); i++) {
			DebugOut("Entity collision\n");
		}
	}
	if (hitpoint < 0) hitpoint = 0;
}

Sophia::~Sophia()
{
}

void Sophia::changeState(int stateId)
{
	if (stateId == COMMON_SOPHIA_IDLE) {
		//check current direction
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT)
			state = SOPHIA_BODY_FLAT_IDLE_LEFT;
		if (state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT)
			state = SOPHIA_BODY_FLAT_IDLE_RIGHT;
		//check if turning animation is completed
		if (state == SOPHIA_BODY_TURN_TO_LEFT) {
			if (turningTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_IDLE_LEFT;
			}
		}
		if (state == SOPHIA_BODY_TURN_TO_RIGHT) {
			if (turningTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_IDLE_RIGHT;
			}
		}
	}
	else if (stateId == SOPHIA_BODY_FLAT_MOVE_LEFT) {
		//check if direction force sophia to turn
		if (state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT || state == SOPHIA_BODY_TURN_TO_RIGHT) {
			state = SOPHIA_BODY_TURN_TO_LEFT;
			turningTimer->restart();
		}
		//check if turning animation is completed
		if (state == SOPHIA_BODY_TURN_TO_LEFT) {
			if (turningTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_MOVE_LEFT;
			}
		}
	}
	else if (stateId == SOPHIA_BODY_FLAT_MOVE_RIGHT) {
		//check if direction force sophia to turn
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_TURN_TO_LEFT) {
			state = SOPHIA_BODY_TURN_TO_RIGHT;
			turningTimer->restart();
		}
		//check if turning animation is completed
		if (state == SOPHIA_BODY_TURN_TO_RIGHT) {
			if (turningTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_MOVE_RIGHT;
			}
		}
	}
	else if (stateId == SOPHIA_GUN_MOUNT_RAISE) {
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT) {
			state = SOPHIA_BODY_SLANT_LEFT;
			gunRaiseTimer->restart();
		}
		else if (state == SOPHIA_BODY_TURN_TO_LEFT) {
			turningTimer->stop();
			state = SOPHIA_BODY_SLANT_LEFT;
			gunRaiseTimer->restart();
		}
		else if (state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT) {
			state = SOPHIA_BODY_SLANT_RIGHT;
			gunRaiseTimer->restart();
		}
		else if (state == SOPHIA_BODY_TURN_TO_RIGHT) {
			turningTimer->stop();
			state = SOPHIA_BODY_SLANT_RIGHT;
			gunRaiseTimer->restart();
		}
		if (state == SOPHIA_BODY_SLANT_LEFT) {
			if (gunRaiseTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_UP_LEFT;
			}
		}
		else if (state == SOPHIA_BODY_SLANT_RIGHT) {
			if (gunRaiseTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_UP_RIGHT;
			}
		}
		//this part involve peeking control state, can be improved
		if (state == SOPHIA_BODY_UP_LEFT && (controlState & RIGHT))
			state = SOPHIA_BODY_UP_RIGHT;
		else if (state == SOPHIA_BODY_UP_RIGHT && (controlState & LEFT))
			state = SOPHIA_BODY_UP_LEFT;
	}
	else if (stateId == SOPHIA_GUN_MOUNT_UNRAISE) {
		if (state == SOPHIA_BODY_UP_LEFT) {
			state = SOPHIA_BODY_SLANT_LEFT;
			gunRaiseTimer->restart();
		}
		else if (state == SOPHIA_BODY_UP_RIGHT) {
			state = SOPHIA_BODY_SLANT_RIGHT;
			gunRaiseTimer->restart();
		}
		else if (state == SOPHIA_BODY_SLANT_LEFT) {
			if (gunRaiseTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_IDLE_LEFT;
			}
		}
		else if (state == SOPHIA_BODY_SLANT_RIGHT) {
			if (gunRaiseTimer->peekState() == TIMER_INACTIVE) {
				state = SOPHIA_BODY_FLAT_IDLE_RIGHT;
			}
		}
	}
	//TODO: opening door state
}

void Sophia::changeMovingState(int stateId)
{
	switch (stateId) {
	case SOPHIA_MOVING_IDLE:
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT)
			movingState = SOPHIA_WHEEL_NORMAL_LEFT_IDLE;
		else if (state == SOPHIA_BODY_SLANT_LEFT)
			movingState = SOPHIA_WHEEL_CLOSE_LEFT_IDLE;
		else if (state == SOPHIA_BODY_UP_LEFT)
			movingState = SOPHIA_WHEEL_CLOSER_LEFT_IDLE;
		else if (state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT)
			movingState = SOPHIA_WHEEL_NORMAL_RIGHT_IDLE;
		else if (state == SOPHIA_BODY_SLANT_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSE_RIGHT_IDLE;
		else if (state == SOPHIA_BODY_UP_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSER_RIGHT_IDLE;
		break;
	case SOPHIA_MOVING_LEFT:
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT)
			movingState = SOPHIA_WHEEL_NORMAL_LEFT;
		else if (state == SOPHIA_BODY_SLANT_LEFT || state == SOPHIA_BODY_SLANT_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSE_LEFT;
		else if (state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_UP_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSER_LEFT;
		break;
	case SOPHIA_MOVING_RIGHT:
		if (state == SOPHIA_BODY_FLAT_IDLE_LEFT || state == SOPHIA_BODY_FLAT_MOVE_LEFT || state == SOPHIA_BODY_FLAT_IDLE_RIGHT || state == SOPHIA_BODY_FLAT_MOVE_RIGHT)
			movingState = SOPHIA_WHEEL_NORMAL_RIGHT;
		else if (state == SOPHIA_BODY_SLANT_LEFT || state == SOPHIA_BODY_SLANT_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSE_RIGHT;
		else if (state == SOPHIA_BODY_UP_LEFT || state == SOPHIA_BODY_UP_RIGHT)
			movingState = SOPHIA_WHEEL_CLOSER_RIGHT;
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