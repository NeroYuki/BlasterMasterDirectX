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
	GameTimer* switchSceneTimer;
	GameTimer* bossSceneTimer;
	GameTimer* bossTimer;
	int isBossFight;
	//BossJoint* bossJointStart=NULL;
	BossJoint* bossjoints1[5];
	BossJoint* bossjoints2[5];
	Boss* boss;
	float tempdx=0, tempdy=0;
	float tempdx2 = 0, tempdy2 = 0;
	int randomx, randomy;
public:
	DebugScene(SceneStateMachine* sceneState);
	void initScene();
	void handlingInput();
	void update(DWORD dt);
	void onActivate();
	void onDeAtivate();
	void renderHUD();
	int getCurrentSceneNumber() { return 2; }
	~DebugScene();
	void jointUpdate();
};