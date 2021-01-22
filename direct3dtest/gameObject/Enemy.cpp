#include "Enemy.h"

Enemy::Enemy(float x, float y, int hp) : GameObject(x, y){
	this->HitPoint = hp;
	dameTakenTimer = new GameTimer(100);
	dyingTimer = new GameTimer(200);
	//this->isDie = 0;
	istakingdmg = 0;
	invincible = 0;
}

void Enemy::render()
{
	LPANIMATION ani;
	LPANIMATION deadani;
	deadani = AnimationManager::getInstance()->get(BULLET_EXPLO);
	ani = AnimationManager::getInstance()->get(state);
	if (this->invincible == 1) {
		deadani->render(this->x , this->y);
	}	
	else {
		if (istakingdmg == 1)ani->render(x, y, D3DCOLOR_RGBA(128, 128, 222, 255));
		else ani->render(x, y);
	}
}

void Enemy::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (this->HitPoint <= 0)
	{
		SoundManager::getInstance()->Play(eSoundId::SOUND_ENEMY_DYING);
		this->invincible = 1;
	}
	short dmgstate = dameTakenTimer->update(dt);
	short deadtimerstate = dyingTimer->update(dt);

	if (dmgstate == TIMER_INACTIVE) {
		if (dmgtaken != 0)
		{
			this->HitPoint -= dmgtaken;
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

	if (deadtimerstate == TIMER_INACTIVE) {
		if (invincible == 1) {
			dyingTimer->restart();
		}
	}
	else if (deadtimerstate == TIMER_STARTED)
	{
		this->vx = 0;
		this->vy = 0;
	}
	else if (deadtimerstate == TIMER_ENDED) {
		int randomdrop;
		Collectable* collectable = NULL;
		randomdrop= SharedData::getInstance()->getRandomNumber();
		randomdrop= randomdrop % 10 + 1;
		CollectableManager::getinstance();
		switch (randomdrop) {
		case 1:collectable = new Collectable(this->x, this->y, 1, 4); break;
		case 2:collectable = new Collectable(this->x, this->y, 1, 4); break;
		case 3:if (spawnPlace == 2)collectable = new Collectable(this->x, this->y, 2, 1); break;
		case 4:if (spawnPlace == 2)collectable = new Collectable(this->x, this->y, 2, 1); break;
		case 5:if (spawnPlace == 2) {
			collectable = new Collectable(this->x, this->y, 2, 1);
		}
			  else collectable = new Collectable(this->x, this->y, 3, 10); 
			break;
		case 6:if (spawnPlace == 2) {
			collectable = new Collectable(this->x, this->y, 2, 1);
		}
			 else 
			collectable = new Collectable(this->x, this->y, 4, 10); 
			break;
		case 7:if (spawnPlace == 2) {
			collectable = new Collectable(this->x, this->y, 2, 1);
		}
			  collectable = new Collectable(this->x, this->y, 5, 10);
		break;
		case 8:collectable = new Collectable(this->x, this->y, 1, 4); break;
		case 9:collectable = new Collectable(this->x, this->y, 1, 4); break;
		default: collectable = new Collectable(this->x, this->y, 1, 4); break;
		}
		if (collectable != NULL)  CollectableManager::getinstance()->addCollectable(collectable);
		this->isDie = 2;
	}
}

Enemy::~Enemy()
{
}
void Enemy::FilterCollisionBlock(std::vector<LPCOLLISIONEVENT>& coEvents, std::vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny, float& rdx, float& rdy)
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

void Enemy::GetHit(int dmg)
{
	if (dmgtaken == 0) this->dmgtaken = dmg;
}
