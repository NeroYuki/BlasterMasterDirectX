#include "Intro.h"

Intro::Intro(SceneStateMachine* sceneState) : Scene(sceneState)
{
	timerunFirstIntro = new GameTimer(20500);
	timerunReady = new GameTimer(5000);
	introID = FIRST_INTRO;
	initScene();
	isEnterKeyDown = 0;
}

void Intro::initScene() {

	timerunFirstIntro->restart();
}

void Intro::handlingInput() {
	if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
		isEnterKeyDown = 1;
	}
	if ((isEnterKeyDown == 1)&&(InputHandler::getInstance()->isKeyDown(DIK_RETURN)==0)) {
		if (introID == FIRST_INTRO) {
			timerunFirstIntro->stop();
			this->changeIntroID(SECOND_INTRO);
		}
		else if (introID == SECOND_INTRO) {
			this->changeIntroID(THIRD_INTRO);
			timerunReady->restart();
		}
		isEnterKeyDown = 0;
	}
}

void Intro::update(DWORD dt) {
	Scene::update(dt);
	short timerState = timerunFirstIntro->update(dt);
	short timerReadyState = timerunReady->update(dt);
	if (timerState == TIMER_ENDED) {
		changeIntroID(SECOND_INTRO);
	}
	if (timerReadyState == TIMER_ENDED) {
		int sceneId = sceneState->getSceneByLabel("DeadScene");
		if (sceneId != -1) {
			sceneState->switchToScene(sceneId);
		}
	}
}

void Intro::render() {
	LPANIMATION introAni = AnimationManager::getInstance()->get(introID);
	introAni->render(0, 0);

}

void Intro::changeIntroID(int newID) {
	introID = newID;
}