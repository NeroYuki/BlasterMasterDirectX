#include "CollectableManager.h"

CollectableManager::CollectableManager() {}
CollectableManager* CollectableManager::instance = nullptr;

CollectableManager* CollectableManager::getinstance() {
	if (!instance)
	{
		instance = new CollectableManager;
	}
	return instance;
}

void CollectableManager::addCollectable(Collectable* collectable)
{
	collectables.push_back(collectable);
}

std::vector<Collectable*>* CollectableManager::getCollectable()
{
	return &(this->collectables);
}