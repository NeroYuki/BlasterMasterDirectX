#include"JasonTop.h"
JasonTop::JasonTop(float x, float y, int hp) : Player(x, y, hp)
{
	vx = 0; vy = 0;
	state = TOP_JASON_IDLE_LEFT;
}

void JasonTop::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void JasonTop::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	vx = 0; vy = 0;
	if (controlState & (DOWN)) vy += PLAYER_WALKING_SPEED;
	if (controlState & (UP)) vy -= PLAYER_WALKING_SPEED;
	if (controlState & (LEFT)) vx -= PLAYER_WALKING_SPEED;
	if (controlState & (RIGHT)) vx += PLAYER_WALKING_SPEED;

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

//NOTE: Turn to pure virtual ASAP after inheiritance is completed
void JasonTop::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y + 18;
	left = this->x;
	bottom = top + BBOX_PLAYER_HEIGHT;
	right = left + BBOX_PLAYER_WIDTH;
}