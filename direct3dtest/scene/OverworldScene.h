#pragma once
#include "Scene.h"
#include "../SceneStateMachine.h"
#include "../InputHandler.h"
#include <stack>

#define OVERWORLD_SCENE_WIDTH 3200
#define OVERWORLD_SCENE_HEIGHT 1600

class OverworldScene : public Scene {
private:
	SceneStateMachine* sceneState;
	std::stack<Player*>* p_stack;
	GameTimer* sectionSwitchTimer;
	GameTimer* blockShiftTimer;
public:
	OverworldScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
};