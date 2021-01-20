#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine()
{
	curScene = NULL;
	preScene = NULL;
}

void SceneStateMachine::handlingInput()
{
	if (curScene == NULL) return;
	curScene->handlingInput();
}

int SceneStateMachine::getBgTextureId()
{
	if (curScene == NULL) return 0;
	return curScene->getBgTexture_id();
}

int SceneStateMachine::getFgTextureId()
{
	if (curScene == NULL) return 0;
	return curScene->getFgTexture_id();
}

Camera* SceneStateMachine::getActiveCamera()
{
	if (curScene == NULL) return NULL;
	return curScene->getCamera();
}

void SceneStateMachine::update(DWORD dt)
{
	if (curScene == NULL) return;
	curScene->update(dt);
}

void SceneStateMachine::render()
{
	if (curScene == NULL) return;
	curScene->render();
}

void SceneStateMachine::renderHUD()
{
	if (curScene == NULL) return;
	curScene->renderHUD();
}

int SceneStateMachine::addScene(Scene* scene, const char* label)
{
	//might fail
	sceneMap[curAssignedId] = scene;
	sceneLabel[curAssignedId] = label;

	sceneMap[curAssignedId]->onCreate();

	curAssignedId++;
	
	return curAssignedId - 1;
}

int SceneStateMachine::getSceneByLabel(const char* query)
{
	for (std::unordered_map<int, const char*>::iterator it = sceneLabel.begin(); it != sceneLabel.end(); ++it) {
		if (strcmp((*it).second, query) == 0) {
			return (*it).first;
		}
	}
	return -1;
}

void SceneStateMachine::switchToScene(int id)
{
	preScene = curScene;
	auto findResult = sceneMap.find(id);
	if (findResult != sceneMap.end()) {
		if (curScene != NULL) {
			curScene->onDeactivated();
		}
		curScene = findResult->second; //get the scene (scene is the second param in pair)
		curScene->onActivate();
	}
}

void SceneStateMachine::removeScene(int id)
{
	auto findResult = sceneMap.find(id);
	if (findResult != sceneMap.end()) {
		if (curScene == findResult->second) {
			curScene = NULL;
		}
		findResult->second->onDestroy();
		//?
		delete findResult->second;
		sceneMap.erase(id);
	}
}

Scene* SceneStateMachine::getSceneById(int id)
{
	if (sceneMap[id] == nullptr) return NULL;
	return sceneMap[id];
}

void SceneStateMachine::switchBackToPreScene()
{

	if (preScene != NULL) {
		Scene* temp = curScene;
		curScene = preScene;
		preScene = temp;
		preScene->onDeactivated();
		curScene->onActivate();
	}
	
}

