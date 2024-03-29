#include "BulletManager.h"

BulletManager::BulletManager() {}
BulletManager* BulletManager::instance = nullptr;

BulletManager* BulletManager::getinstance() {
	if (!instance)
	{
		instance = new BulletManager;
	}
	return instance;
}

void BulletManager::addBullet(Bullet* bullet)
{
	bullets.push_back(bullet);
//	currenbullets.push_back(bullet);
}

void BulletManager::removeBullet(Bullet* bullet)
{
	deletebullets.push_back(bullet);
//	currenbullets.erase(std::remove(currenbullets.begin(), currenbullets.end(), bullet));
}

std::vector<Bullet*> *BulletManager::getBullet()
{
	return &(this->bullets);
}

std::vector<Bullet*>* BulletManager::getDeleteBullet()
{
	return &(this->deletebullets);
}
//std::vector<Bullet*>* BulletManager::getCurrentBullet()
//{
//	return &(this->currenbullets);
//}



