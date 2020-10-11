#include "Scene.h"

Scene::Scene()
{
	//this->sceneState = sceneState;
}

void Scene::addObject(GameObject* obj)
{
	objectPool.push_back(obj);
}

void Scene::update(DWORD dt)
{
	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
		(*it)->update(dt);
	}
}

void Scene::render()
{
	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
		(*it)->render();
	}
}
