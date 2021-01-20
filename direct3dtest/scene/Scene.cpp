#include "Scene.h"

Scene::Scene(SceneStateMachine* sceneState)
{
	this->sceneState = sceneState;
	cam = new Camera();
	heatlhbar = new HeatlhBar();
	gunBar = new GunBar();
}

void Scene::addObject(GameObject* obj)
{
	objectGridMap.push_back(new ObjectGrid(obj));
}

// costly operation, use with caution
bool Scene::removeObject(GameObject* obj)
{
	//TODO: improve this (might not even be possible due to how objectGridMap is built)
	for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it) {
		if ((*it)->getObj() == obj) {
			ObjectGrid* toBeDeleted = (*it);
			//iterate through coObjects in case deleted object is pushed to this list
			for (std::vector<GameObject*>::iterator i_it = coObjects.begin(); i_it != coObjects.end(); ++i_it) {
				if ((*i_it) == obj) {
					coObjects.erase(i_it);
					break;
				}
			}
			objectGridMap.erase(it);
			delete toBeDeleted->getObj();
			delete toBeDeleted;
			break;
		}
	}
	return false;
}

void Scene::addSection(SceneSection* section)
{
	sectionGraph.addSection(section);
}

void Scene::addPortal(Portal* p)
{
	addObject(p);
	sectionGraph.addPortal(p);
}

void Scene::update(DWORD dt)
{

	if (activeSection != -1) {
		cam->update(sectionGraph.getSection(activeSection));

	}
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
	for (int i = 0; i < coObjects.size(); i++) {
		if (coObjects.at(i)->getisDie() == 1) {
			if (dynamic_cast<Enemy*>(coObjects.at(i)))
				SoundManager::getInstance()->Play(eSoundId::SOUND_ENEMY_DYING);
			removeObject(coObjects.at(i));
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

bool Scene::resetSceneEnemy()
{
	coObjects.clear();
	for (int i = objectGridMap.size() - 1; i >= 0; i--) {
		if (dynamic_cast<Enemy*>(objectGridMap.at(i)->getObj())) {
			ObjectGrid* toBeDeleted = objectGridMap.at(i);
			objectGridMap.erase(objectGridMap.begin() + i);
			delete toBeDeleted->getObj();
			delete toBeDeleted;

		}
		else if (dynamic_cast<Player*>(objectGridMap.at(i)->getObj())) {
			objectGridMap.at(i)->updateGridPos();
		}
		
	}

	if (this->getCurrentSceneNumber()>0) {
		if (this->getCurrentSceneNumber() == 1) {
			ResourceImporter::enemyImport("resource\\map_data\\overworld_entityData.txt", this);
			return true;
		}
		else if (this->getCurrentSceneNumber() == 2) {
			ResourceImporter::enemyImport("resource\\map_data\\dungeon_entityData.txt", this);
			return true;
		}
	}

}




