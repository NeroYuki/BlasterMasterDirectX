#include "Cannon.h"

Cannon::Cannon(float x, float y, int hp) : Enemy(x,y,hp)
{
	this->state = CANON_IDLE;
	this->HitPoint = hp;
	interval = new GameTimer(500);
	spawnPlace = 2;
}

void Cannon::render()
{
	Enemy::render();
}

void Cannon::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::update(dt,coObjects);
	if (this->isDie == 2) this->isDie = 1;
	GameObject::update(dt);
	short timestate = interval->update(dt);
	if (timestate == TIMER_INACTIVE) {
		canonstate++;
		if (canonstate == 5) canonstate = 1;
		switch (canonstate) {
		case 1:
			this->state = CANON_IDLE; break;
		case 2:
			this->state = CANON_TOPDOWN;
			SoundManager::getInstance()->Play(eSoundId::SOUND_TELEPORTER_SHOOTING);
			new EnemyBullet(this->x + 8, this->y, 0, -0.2, 4);
			new EnemyBullet(this->x + 8, this->y+16, 0, 0.2, 4);
			break;
		case 3:
			this->state = CANON_IDLE; break;
		case 4:
			this->state = CANON_LEFTRIGHT;
			SoundManager::getInstance()->Play(eSoundId::SOUND_TELEPORTER_SHOOTING);
			new EnemyBullet(this->x , this->y+8, -0.2, 0, 4);
			new EnemyBullet(this->x +16, this->y+8, 0.2, 0, 4);
		default:
			this->state = CANON_IDLE; break;
		}
		interval->restart();
	}
}

void Cannon::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_CANNON_HEIGHT;
	right = left + BBOX_CANNON_WIDTH;
}

Cannon::~Cannon()
{
}
