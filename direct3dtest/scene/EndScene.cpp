#include "EndScene.h"

EndScene::EndScene(SceneStateMachine* sceneState) : Scene(sceneState) 
{
	bgTexture_id = 19;
	timerunEndingAni = new GameTimer(5600);
	timerunTreeAni = new GameTimer(500);
	startTrans = false;
	stopTrans = false;
	countTreeAni = 0;
	initScene();
}
void EndScene::initScene() {
	timerunEndingAni->restart();
	timerunTreeAni->restart();
}

void EndScene::handlingInput() {

}

void EndScene::update(DWORD dt) {
	if (startTrans == true) {
		if (cam->getX() != 257) {
			cam->transform(1.0f, 0);
		}
		else {
			stopTrans = true;
		}
	}
	Scene::update(dt);
	short timerRunState = timerunEndingAni->update(dt);
	short timerTreeState = timerunTreeAni->update(dt);
	if (timerRunState == TIMER_ENDED) {
		startTrans = true;
	}
	if (countTreeAni < 8) {
		if (timerTreeState == TIMER_ENDED) {
			countTreeAni += 1;
			timerunTreeAni->restart();
		}
	}
}


void EndScene::render() {
	LPANIMATION endAni = AnimationManager::getInstance()->get(200001);
	LPANIMATION	carEnding = AnimationManager::getInstance()->get(200002);
	if (startTrans == false) {
		endAni->render(0, 0);
	}
	if (stopTrans == true) {
		carEnding->render(370, 95);
	}
	if (countTreeAni < 8) {
		LPANIMATION treeAni = AnimationManager::getInstance()->get(300000 + countTreeAni);
		treeAni->render(121, 114 + countTreeAni * 3);
	}
}