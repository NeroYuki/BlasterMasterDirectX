#pragma once
#include "Scene.h"
#include "../InputHandler.h"
#include <stack>

#define DEBUG_SCENE_WIDTH 3200
#define DEBUG_SCENE_HEIGHT 1600

class DebugScene : public Scene {
private:
	std::stack<Player*>* p_stack;
	GameTimer* sectionSwitchTimer;
public:
	DebugScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	~DebugScene();
};