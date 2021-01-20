#include "DeadScene.h"

DeadScene::DeadScene(SceneStateMachine* sceneState) : Scene(sceneState)
{
	initScene();
	choice = 1;
	bgTexture_id = 25;
	fgTexture_id = -1;
}

void DeadScene::initScene()
{
	this->live = SharedData::getInstance()->remaininglive;
	charsets[0] = new CharsetShow(88, 100, STILL_ALIVE_SCENE);
	charsets[1] = new CharsetShow(88, 100, DEAD_SCENE);
	charsets[2] = new CharsetShow(60, 100, DEADSCENE_CHOICE);
	charsets[3] = new CharsetShow(174, 100, CHARSET_0);
}

void DeadScene::handlingInput()
{

	if (InputHandler::getInstance()->isKeyDown(DIK_DOWN)) {
		isdownkeydown = 1;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_UP)) {
		isupkeydown = 1;
	}
	if (isdownkeydown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_DOWN) == 0) {
			if (choice <2 ) {
				choice += 1;
			}
			isdownkeydown = 0;
		}
	}
	if (isupkeydown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_UP) == 0) {
			if (choice >1) {
				choice -= 1;
			}
			isupkeydown = 0;
		}
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
		isEnterKeyDown = 1;
	}
	if (isEnterKeyDown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_RETURN) == 0) {
			isEnterKeyDown = 0;
			if (fromintro == 1) {

				fromintro = 0;
				int sceneId = sceneState->getSceneByLabel("Overworld");
				if (sceneId != -1) {
					sceneState->switchToScene(sceneId);
				}
			}
			else 
			if (live == 0) {
				if (choice == 1) {
					SharedData::getInstance()->remaininglive = 3;
					sceneState->switchBackToPreScene();
				}
				else if (choice == 2) {
					int id =sceneState->getSceneByLabel("Intro");
					sceneState->switchToScene(id);
				}
				SharedData::getInstance()->remaininglive=3;
			}
			else if (live > 0) {
				sceneState->switchBackToPreScene();
			}

		}
	}
}

void DeadScene::update(DWORD dt)
{
	if (choice == 1) {
		charsets[2]->y = 100;
	}
	else if (choice == 2)
		charsets[2]->y = 110;
	charsets[3]->state = 60000 + live;
	Scene::update(dt);
}

void DeadScene::onActivate()
{
	this->live =SharedData::getInstance()->remaininglive;
	SharedData::getInstance()->remaininglive -= 1;
}

void DeadScene::onDeactivated()
{

}

void DeadScene::render()
{
	LPANIMATION ani;
	if (live <= 0)
	{
		ani = AnimationManager::getInstance()->get(charsets[1]->state);
		ani->render(charsets[1]->x, charsets[1]->y);
		ani = AnimationManager::getInstance()->get(charsets[2]->state);
		ani->render(charsets[2]->x, charsets[2]->y);
	}
	else {
		ani = AnimationManager::getInstance()->get(charsets[0]->state);
		ani->render(charsets[0]->x, charsets[0]->y);
		ani = AnimationManager::getInstance()->get(charsets[3]->state);
		ani->render(charsets[3]->x, charsets[3]->y);
	}
}
