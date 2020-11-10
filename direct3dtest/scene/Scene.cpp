#include "Scene.h"

Scene::Scene()
{
	//this->sceneState = sceneState;
	cam = new Camera();
}

void Scene::addObject(GameObject* obj)
{
	objectGridMap.push_back(new ObjectGrid(obj));
}

void Scene::addSection(SceneSection* section)
{
	sectionList.push_back(section);
}

void Scene::update(DWORD dt)
{
	if (activeSection != -1)
		cam->update(sectionList.at(activeSection));
	else {
		cam->update(nullptr);
	}

	short const gridX_origin = cam->getX() / (SCREEN_WIDTH / 2), gridY_origin = cam->getY() / (SCREEN_HEIGHT / 2);
	coObjects.clear();
	//TODO: use grid algo to reduce the size of coObject
	for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it)
	{
		if ((*it)->isNearby(gridX_origin, gridY_origin)) {
			coObjects.push_back((*it)->getObj());
		}
	}

	for (std::vector<GameObject*>::iterator it = coObjects.begin(); it != coObjects.end(); ++it) {
		(*it)->update(dt, &coObjects);
	}

	for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it)
	{
		if ((*it)->isNearby(gridX_origin, gridY_origin)) {
			(*it)->updateGridPos();
		}
	}
}

void Scene::render()
{
	for (std::vector<GameObject*>::iterator it = coObjects.begin(); it != coObjects.end(); ++it) {
		(*it)->render();
		//(*it)->renderBoundingBox();
	}
}
