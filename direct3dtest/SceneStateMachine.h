#pragma once
#include "scene/Scene.h"

class SceneStateMachine
{
private:
	std::unordered_map<int, Scene*> sceneMap;
	Scene* curScene;
	int curAssignedId = 0;
	
public:
	SceneStateMachine();
	void handlingInput();
	int getBgTextureId();
	int getFgTextureId();
	Camera* getActiveCamera();

	void update(DWORD dt);
	void render();

	int addScene(Scene* scene);
	void switchToScene(int id);
	void removeScene(int id);
	Scene* getSceneById(int id);
};

