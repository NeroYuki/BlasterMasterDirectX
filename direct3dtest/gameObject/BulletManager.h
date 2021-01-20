#pragma once
class Bullet;

#include "Bullet.h"
#include <algorithm>

class BulletManager {
private:
	static BulletManager* instance;
	std::vector<Bullet*> bullets;
	std::vector<Bullet*> deletebullets;
	BulletManager();
public:
	static BulletManager* getinstance();
	void addBullet(Bullet* bullet);
	void removeBullet(Bullet* bullet);
	std::vector<Bullet*>* getBullet();
	std::vector<Bullet*>* getDeleteBullet();
};