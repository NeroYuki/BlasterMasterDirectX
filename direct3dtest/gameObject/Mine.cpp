#include "Mine.h"

Mine::Mine(float x, float y, int hp) : Enemy(x, y, hp)
{
	this->state = MINE_TICK;
	this->x = x;
	this->y = y ;
	this->HitPoint = 1;
	explo = 0;
	spawnPlace = 1;

}

void Mine::render()
{

	Enemy::render();
}

void Mine::update(DWORD dt, std::vector<LPGAMEOBJECT>* coObjects)
{
	if (!SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_MINE_TICKING))
		SoundManager::getInstance()->Play(eSoundId::SOUND_MINE_TICKING);
	Enemy::update(dt, coObjects);
	if (this->isDie == 2 ) {
		if (SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_MINE_TICKING)) {
			SoundManager::getInstance()->Stop(eSoundId::SOUND_MINE_TICKING);

		}
		new EnemyBullet(this->x + 3, this->y, 0.075, 0, 3);
		new EnemyBullet(this->x + 3, this->y, -0.05, 0, 3);
		new EnemyBullet(this->x + 3, this->y, 0, 0, 3);
		this->isDie = 1;
	}
	GameObject::update(dt);
}

void Mine::GetBoundingBox(float& top, float& left, float& bottom, float& right)
{
	top = this->y;
	left = this->x;
	bottom = top + BBOX_MINE_HEIGHT;
	right = left + BBOX_MINE_WIDTH;
}

Mine::~Mine()
{
}
