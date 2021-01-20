#pragma once
class Scene;

#include "scene/Scene.h"

class SceneStateMachine
{
private:
	std::unordered_map<int, Scene*> sceneMap;
	std::unordered_map<int, const char*> sceneLabel;
	Scene* curScene;
	int curAssignedId = 0;
	Scene* preScene ;
public:
	SceneStateMachine();
	void handlingInput();
	int getBgTextureId();
	int getFgTextureId();
	Camera* getActiveCamera();
	void update(DWORD dt);
	void render();
	void renderHUD();

	int addScene(Scene* scene, const char* label = "Unknown");
	int getSceneByLabel(const char* query);
	void switchToScene(int id);
	void removeScene(int id);
	Scene* getSceneById(int id);
	void switchBackToPreScene();
};

