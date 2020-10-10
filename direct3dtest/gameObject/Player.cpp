#include "Player.h"

Player::Player(float x, float y, int hp) : GameObject(x,y)
{
}

void Player::render()
{
}

void Player::update(DWORD dt)
{
}

Player::~Player()
{
}

void Player::changeState(int stateId)
{
	switch (state) {
	case PLAYER_IDLE:
		if (stateId == PLAYER_WALK)
			state = stateId;
		break;
	}
}
