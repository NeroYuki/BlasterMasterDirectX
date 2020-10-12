#pragma once
#include "Scene.h"
#include "../SceneStateMachine.h"
#include "../InputHandler.h"

class DebugScene : public Scene {
private:
	SceneStateMachine* sceneState;
	Player* p;
public:
	DebugScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update();
};