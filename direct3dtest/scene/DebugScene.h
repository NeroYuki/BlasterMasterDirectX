#pragma once
#include "Scene.h"
#include "../SceneStateMachine.h"
#include "../InputHandler.h"

#define SCENE_WIDTH 3200
#define SCENE_HEIGHT 1600

class DebugScene : public Scene {
private:
	SceneStateMachine* sceneState;
	JasonTop* jsTop;
	Jason* js;
	Sophia* sophia;
public:
	DebugScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update();
};