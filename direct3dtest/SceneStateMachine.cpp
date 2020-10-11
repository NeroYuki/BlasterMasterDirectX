#include "SceneStateMachine.h"

SceneStateMachine::SceneStateMachine()
{
	curScene = NULL;
}

void SceneStateMachine::handlingInput()
{
	if (curScene == NULL) return;
	curScene->handlingInput();
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

int SceneStateMachine::addScene(Scene* scene)
{
	//might fail
	sceneMap[curAssignedId] = scene;

	sceneMap[curAssignedId]->onCreate();

	curAssignedId++;
	
	return curAssignedId - 1;
}

void SceneStateMachine::switchToScene(int id)
{
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