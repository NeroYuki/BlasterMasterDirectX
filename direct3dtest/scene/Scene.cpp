#include "Scene.h"

Scene::Scene()
{
	//this->sceneState = sceneState;
	cam = new Camera();
}

void Scene::addObject(GameObject* obj)
{
	objectPool.push_back(obj);
}

void Scene::update(DWORD dt)
{
	cam->update();
	std::vector<LPGAMEOBJECT> coObjects;
	//todo: use grid algo to reduce the size of coObject
	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it)
	{
		coObjects.push_back(*it);
	}

	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
		(*it)->update(dt, &coObjects);
	}
}

void Scene::render()
{
	for (std::vector<GameObject*>::iterator it = objectPool.begin(); it != objectPool.end(); ++it) {
		(*it)->render();
	}
}
