#include"Jason.h"
Jason::Jason(float x, float y, int hp) : Player(x,y,hp)
{
	vx = 0; vy = 0;
	state = JASON_IDLE_LEFT;
}

void Jason::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Jason::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	//vy += 0.02;
	vx = 0; 
	//if (controlState & (DOWN)) vy += PLAYER_WALKING_SPEED;
	if (controlState & (LEFT)) vx -= PLAYER_WALKING_SPEED;
	if (controlState & (RIGHT)) vx += PLAYER_WALKING_SPEED;
	if (controlState & (PRIMARY)) vy -= JASON_JUMP_SPEED;

	GameObject::update(dt);


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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		//float t, l, b, r;
		//coEvents[0]->obj->GetBoundingBox(t, l, b, r);
		//std::string s1 = std::to_string(t);
		//std::string s2 = std::to_string(l);
		//DebugOut(s1.c_str());
		//DebugOut("\n");
		//DebugOut(s2.c_str());
		//DebugOut("\n\n");

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
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
	case COMMON_JASON_IDLE:
		if (state == JASON_WALK_LEFT || state == JASON_CRAW_IDLE_LEFT || state == JASON_CRAW_LEFT) state = JASON_IDLE_LEFT;
		else if (state == JASON_WALK_RIGHT || state == JASON_CRAW_IDLE_RIGHT || state == JASON_CRAW_RIGHT) state = JASON_IDLE_RIGHT;
		else break;
		break;
	case COMMON_JASON_CRAW_IDLE:
		if (state == JASON_WALK_LEFT || state == JASON_IDLE_LEFT || state == JASON_CRAW_LEFT || state == JASON_CRAW_IDLE_LEFT)
			state = JASON_CRAW_IDLE_LEFT;
		else if (state == JASON_WALK_RIGHT || state == JASON_IDLE_RIGHT || state == JASON_CRAW_RIGHT || state == JASON_CRAW_IDLE_RIGHT)
			state = JASON_CRAW_IDLE_RIGHT;
		else break;
		break;
	default:
		state = stateId;
	}
}

//NOTE: Turn to pure virtual ASAP after inheiritance is completed
void Jason::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y + 18;
	left = this->x;
	bottom = top + BBOX_PLAYER_HEIGHT;
	right = left + BBOX_PLAYER_WIDTH;
}