#pragma once
#include "Scene.h"
#include "../InputHandler.h"
#include <stack>

#define OVERWORLD_SCENE_WIDTH 3200
#define OVERWORLD_SCENE_HEIGHT 1600

class OverworldScene : public Scene {
private:
	std::stack<Player*>* p_stack;
	GameTimer* sectionSwitchTimer;
	GameTimer* blockShiftTimer;
	GameTimer* switchSceneTimer;
public:
	OverworldScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void onActivate();
	void onDeactivated() ;
	void renderHUD();
	int getCurrentSceneNumber() { return 1; }
};