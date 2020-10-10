#include "Scene.h"

Scene::Scene()
{
}

void Scene::addObject(GameObject* obj)
{
	objectPool.push_back(obj);
}

void Scene::render()
{
	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
		(*it)->render();
	}
}
