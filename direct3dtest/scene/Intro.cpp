#include"Intro.h"


Intro::Intro(SceneStateMachine* sceneState) : Scene(), sceneState(sceneState)
{
	timerunFirstIntro = new GameTimer(19500);
	introID = FIRST_INTRO;
	initScene();

}

void Intro::initScene() {

	timerunFirstIntro->restart();
}

void Intro::handlingInput() {
	if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
		this->changeIntroID(THIRD_INTRO);
	}
}

void Intro::update(DWORD dt) {
	Scene::update(dt);
	short timerState = timerunFirstIntro->update(dt);
	if (timerState == TIMER_ENDED) {
		changeIntroID(SECOND_INTRO);
	}
}

void Intro::render() {
	LPANIMATION introAni = AnimationManager::getInstance()->get(introID);
	introAni->render(0, 0);

}

void Intro::changeIntroID(int newID) {
	introID = newID;
}