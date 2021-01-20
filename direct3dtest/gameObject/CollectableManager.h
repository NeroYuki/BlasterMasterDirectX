#pragma once
class Collectable;

#include "Collectable.h"
#include <algorithm>

class CollectableManager {
private:
	static CollectableManager* instance;
	std::vector<Collectable*> collectables;
	CollectableManager();
public:
	static CollectableManager* getinstance();
	void addCollectable(Collectable* collectable);
	std::vector<Collectable*>* getCollectable();
};