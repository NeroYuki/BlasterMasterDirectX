#include "Player.h"
#include <string>

Player::Player(float x, float y, int hp) : GameObject(x,y)
{
	vx = 0; vy = 0;
	dameTakenTimer = new GameTimer(500);
	inDeadAniTimer = new GameTimer(300);
	//this->isDie = 0;
	istakingdmg = 0;
	invincible = 0;
}

void Player::render()
{
	LPANIMATION ani;
	ani = AnimationManager::getInstance()->get(state);
	ani->render(x, y);
}

void Player::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (hitpoint <= 0) this->invincible = 1;

	short dmgstate = dameTakenTimer->update(dt);
	short deadtimerstate = inDeadAniTimer->update(dt);
	if (checkSpiked() == 1) {
		this->PlayerGetHit(1);
	}
	if (this->hitpoint > 16) {
		this->hitpoint = 16;
	}
	if (invincible == 0) {
		if (dmgstate == TIMER_INACTIVE) {
			if (dmgtaken != 0)
			{
				SoundManager::getInstance()->Play(eSoundId::SOUND_JASON_HURTING);
				this->hitpoint -= dmgtaken;
				dmgtaken = 0;
				istakingdmg = 0;
				dameTakenTimer->restart();
			}
		}
		else if (dmgstate == TIMER_ACTIVE) {
			if (istakingdmg == 1)istakingdmg = 0;
			else istakingdmg = 1;
		}
		else if (dmgstate == TIMER_ENDED) {
			istakingdmg = 0;
		}
	}
	else {
		this->dmgtaken = 0;
	}

	if (deadtimerstate == TIMER_INACTIVE) {
		if (invincible == 1) {
			SoundManager::getInstance()->Play(eSoundId::SOUND_SOPHIA_DYING);
			
			inDeadAniTimer->restart();
		}
	}


	else if (deadtimerstate == TIMER_STARTED)
	{
		this->vx = 0;
		this->vy = 0;
		controlState = 0;
	}
	else if (deadtimerstate == TIMER_ENDED) {
		this->isDie = 2;
	}


	//for (UINT i = 0; i < coObjects->size(); i++)
	//{

	//	if (dynamic_cast<Enemy*>(coObjects->at(i)))
	//	{
	//		float px1, py1,px2,py2;
	//		float px3, py3, px4, py4;
	//		Enemy* p = dynamic_cast<Enemy*>(coObjects->at(i));
	//		p->GetBoundingBox(py1, px1,py2,px2);
	//		this->GetBoundingBox(py3, px3, py4, px4);
	//		px3 = (px3 + px4) / 2;
	//		py3 = (py3 + py4) / 2;
	//		if (px3 >= px1 && px3 <= px2) {
	//			if (py3 >= py1 && py3 <= py2) {
	//				this->PlayerGetHit(2);
	//			}
	//		}
	//		break;
	//	}
	//}
}

Player::~Player()
{
}

void Player::changeState(int stateId)
{
	this->state = stateId;
}

void Player::FilterCollisionBlock(std::vector<LPCOLLISIONEVENT> &coEvents, std::vector<LPCOLLISIONEVENT> &coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	LPCOLLISIONEVENT minimum_x_event = nullptr;
	LPCOLLISIONEVENT minimum_y_event = nullptr;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (dynamic_cast<Block*>(c->obj) == nullptr) {
			continue;
		}

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; minimum_x_event = c; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; minimum_y_event = c; min_iy = i; rdy = c->dy;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) {
		if (dynamic_cast<Block*>(coEvents[i]->obj)) {
			LPCOLLISIONEVENT ci = coEvents[i];
			coEvents.erase(coEvents.begin() + i);
			i--;
			if (ci != minimum_x_event && ci != minimum_y_event) {
				delete ci;
			}
		}
	}

	if (minimum_x_event != nullptr) coEventsResult.push_back(minimum_x_event);
	if (minimum_y_event != nullptr) coEventsResult.push_back(minimum_y_event);

	
}

void Player::resetPlayer(float x, float y)
{
	this->setPos(x, y);
	this->hitpoint = 16;
	this->isDie = -1;
	this->istakingdmg = 0;
	this->invincible = 0;

}

int Player::checkSpiked()
{

	if (this->contactedSpike != NULL) {
		float x1, x2, y1, y2;
		float x3, x4, y3, y4;
		contactedSpike->GetBoundingBox(y1, x1, y2, x2);
		//x1 = (x1 + x2) / 2;
		//y1 = (y1 + y2) / 2;
		this->GetBoundingBox(y3, x3, y4, x4);

		if ((x1 - x4) < 0 && (x2 - x3) > 0){
			if ((y1-y4)<0 && (y2-y3)>0){
				return 1;
			}
		}
	}
	this->contactedSpike = NULL;
	return 0;
}

