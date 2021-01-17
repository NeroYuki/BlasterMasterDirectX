#include"Jason.h"

Jason::Jason(float x, float y, int hp, int activeSection) : Player(x,y,hp)
{
	vx = 0; vy = 0;
	state = JASON_IDLE_LEFT;
	this->activeSection = activeSection;
}

void Jason::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Jason::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (forceControlState != IDLE) {
		controlState = forceControlState;
	}


	if (controlState & (LEFT | RIGHT)) {

		//NOTE: body state is controlled by input
		if ((controlState & (LEFT)) && (!(controlState & (RIGHT)))) {
			if (vx >= -JASON_MOVE_SPEED_CAP)
				vx -= JASON_MOVE_ACCEL;
			else vx == -JASON_MOVE_SPEED_CAP;
			changeState(JASON_WALK_LEFT);
		}
		else if (controlState & (RIGHT) && (!(controlState & (LEFT)))) {
			if (vx <= JASON_MOVE_SPEED_CAP)
				vx += JASON_MOVE_ACCEL;
			else vx == JASON_MOVE_SPEED_CAP;
			changeState(JASON_WALK_RIGHT);
		}
		else {
			if (vx > 0.011) vx -= JASON_MOVE_ACCEL;
			else if (vx < -0.011) vx += JASON_MOVE_ACCEL;
			else vx = 0;
			changeState(COMMON_JASON_IDLE);
		}
	}
	else {
		if (vx > 0.011) vx -= JASON_MOVE_ACCEL;
		else if (vx < -0.011) vx += JASON_MOVE_ACCEL;
		else vx = 0;
		changeState(COMMON_JASON_IDLE);
	}
	

	if (controlState & (PRIMARY)) {
		if (!isOnAir) {
			vy -= JASON_JUMP_SPEED;
			isOnAir = true;
		}
	}
	else {
		if (vy < 0) vy = 0;
	}
	vy += 0.01;

	followingLadder = isOnLadder(coObjects);
	if (followingLadder != NULL) { vy = 0; };

	if (controlState & (DOWN)) {
		if (isCloseToSophia == false) {
			if (isOnScenePortal(coObjects)!=NULL) {
				ScenePortal* portal = isOnScenePortal(coObjects);

			}
			else if (followingLadder != NULL) {
				float tempx, tempy;
				followingLadder->getPos(tempx, tempy);
				this->x = tempx + 4;
				if (this->y < tempy+216) {
					vy = 0.1;
				}
				else vy = 0;
				if (this->state == JASON_CLIMB) { this->state = JASON_CLIMB_IDLE; }
				else this->state = JASON_CLIMB;
			}
			else {
				is_craw = -is_craw;
			}
		}
	}
	if (controlState & (UP)) {
		if (isCloseToSophia == false) {
			if (followingLadder != NULL) {
				float tempx, tempy;
				followingLadder->getPos(tempx, tempy);
				this->x = tempx+4;
				if (this->y >= tempy+1) {
					vy = -0.1;
				}
				else vy = 0;
				if (this->state == JASON_CLIMB) { this->state = JASON_CLIMB_IDLE; }
				else this->state = JASON_CLIMB;
			}
		}
	}


	GameObject::update(dt);

	std::vector<LPCOLLISIONEVENT> coEvents;
	std::vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	bool foundNearSophia = false;

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
		

		if (coEventsResult.size() > 0) {

			if (!ignoreCollision) x += min_tx * dx + nx * 0.4f;
			else x += dx;
			y += min_ty * dy + ny * 0.4f;
			if (nx != 0) vx = 0;
			if (ny < 0) { isOnAir = false; }
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Portal*>(e->obj))
				{
					Portal* p = dynamic_cast<Portal*>(e->obj);
					if (!ignoreCollision) this->activeSection = p->getSectionEnd();
				}
			}
		}
		else {
			x += dx;
			y += dy;
		}

		//for (UINT i = 0; i < coEvents.size(); i++) {
		//	LPCOLLISIONEVENT e = coEvents[i];
		//	if (dynamic_cast<Sophia*>(e->obj)) {
		//		DebugOut("Sophia\n");
		//		foundNearSophia = true;
		//	}
		//}
	
	}

	if (this->followingSophia != NULL) {
		float tempx, tempy;
		this->followingSophia->getPos(tempx, tempy);
		isCloseToSophia = false;
		if (this->x > tempx && this->x < tempx + 30) {
			if (this->y + 10 > tempy && this->y < tempy + 48) {
				DebugOut("Sophia\n");
				//foundNearSophia = true;
				isCloseToSophia = true;
			}
		}
	}
	//if (foundNearSophia) isCloseToSophia = true;
	//else isCloseToSophia = false;
}

Jason::~Jason()
{
}

void Jason::changeState(int stateId)
{
	switch (stateId) {
		//case COMMON_PLAYER_IDLE:
		//	state = stateId;
		//	break;
	case JASON_WALK_LEFT:
		if (is_craw) state = JASON_CRAW_LEFT;
		else state = JASON_WALK_LEFT;
		break;
	case JASON_WALK_RIGHT:
		if (is_craw) state = JASON_CRAW_RIGHT;
		else state = JASON_WALK_RIGHT;
		break;
	case COMMON_JASON_IDLE:
		if (state == JASON_WALK_LEFT || state == JASON_CRAW_IDLE_LEFT || state == JASON_CRAW_LEFT) state = JASON_IDLE_LEFT;
		else if (state == JASON_WALK_RIGHT || state == JASON_CRAW_IDLE_RIGHT || state == JASON_CRAW_RIGHT) state = JASON_IDLE_RIGHT;
		if (is_craw) {
			if (state == JASON_WALK_LEFT || state == JASON_IDLE_LEFT || state == JASON_CRAW_LEFT || state == JASON_CRAW_IDLE_LEFT)
				state = JASON_CRAW_IDLE_LEFT;
			else if (state == JASON_WALK_RIGHT || state == JASON_IDLE_RIGHT || state == JASON_CRAW_RIGHT || state == JASON_CRAW_IDLE_RIGHT)
				state = JASON_CRAW_IDLE_RIGHT;
		}
		break;
	//TODO: climb state
	default:
		state = stateId;
	}
}

void Jason::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_JASON_HEIGHT;
	right = left + BBOX_JASON_WIDTH;
}

void Jason::setFollow(Player* followingSophia)
{
	this->followingSophia = followingSophia;
}

void Jason::unfollow()
{
	this->followingSophia = NULL;
	this->followingLadder = NULL;
}

Ladder* Jason::isOnLadder(std::vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<Ladder*>(coObjects->at(i))) {
			Ladder* ladder= dynamic_cast<Ladder*>(coObjects->at(i));
			float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			ladder->GetBoundingBox(y1, x1, y2, x2);
			x1 = x1 - this->x;
			x2 = x2 - this->x- 8;
			y1 = y1 - this->y;
			y2 = y2 - this->y -16 ;
			if ((x1 < 0 && x2>0) && (y1 < 0 && y2>0)) {
				return ladder;
			}
		}
	}
	return NULL;
}
ScenePortal* Jason::isOnScenePortal(std::vector<LPGAMEOBJECT>* coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++) {
		if (dynamic_cast<ScenePortal*>(coObjects->at(i))) {
			ScenePortal* portal = dynamic_cast<ScenePortal*>(coObjects->at(i));
			float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
			portal->GetBoundingBox(y1, x1, y2, x2);
			x1 = x1 - this->x;
			x2 = x2 - this->x - 8;
			y1 = y1 - this->y;
			y2 = y2 - this->y - 16;
			if ((x1 < 0 && x2>0) && (y1 < 0 && y2>0)) {
				return portal;
			}
		}
	}
	return NULL;
}

