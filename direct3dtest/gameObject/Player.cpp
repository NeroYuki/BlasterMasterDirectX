#include "Player.h"

Player::Player(float x, float y, int hp) : GameObject(x,y)
{
	vx = 0; vy = 0;
	state = TOP_JASON_IDLE_LEFT;
}

void Player::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Player::update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (state == TOP_JASON_WALK_DOWN) vy = WALKING_SPEED;
	else if (state == TOP_JASON_WALK_UP) vy = -WALKING_SPEED;
	else if (state == TOP_JASON_WALK_LEFT) vx = -WALKING_SPEED;
	else if (state == TOP_JASON_WALK_RIGHT) vx = WALKING_SPEED;
	else { vx = 0; vy = 0; }

}

Player::~Player()
{
}

void Player::changeState(int stateId)
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
