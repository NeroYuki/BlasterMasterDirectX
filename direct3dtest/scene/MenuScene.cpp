#include "MenuScene.h"
#pragma once

MenuScene::MenuScene(SceneStateMachine* sceneState)  : Scene(sceneState)
{
	initScene();
	bgTexture_id = 24;
	fgTexture_id = -1;
}

void MenuScene::initScene()
{
	choice = SharedData::getInstance()->weapon;
	int tempstate = 60000;
	SharedData* shareddate = SharedData::getInstance();
	int temp1 = shareddate->homingMissle;
	int temp2 = shareddate->lightning;
	int temp3 = shareddate->x3Missle;
	charsets[0] = new CharsetShow(89, 169, POWER_UP_HOMINGMISSLE);
	charsets[1] = new CharsetShow(121, 169, POWER_UP_THUNDER);
	charsets[2] = new CharsetShow(153, 169, POWER_UP_X3MISSLE);
	charsets[3] = new CharsetShow(89, 184, tempstate + temp1 / 10);
	charsets[4] = new CharsetShow(97, 184, tempstate + temp1 % 10);
	charsets[5] = new CharsetShow(121, 184, tempstate + temp2 / 10);
	charsets[6] = new CharsetShow(129, 184, tempstate + temp2 % 10);
	charsets[7] = new CharsetShow(153, 184, tempstate + temp3 / 10);
	charsets[8] = new CharsetShow(161, 184, tempstate + temp3 % 10);

}

void MenuScene::handlingInput()
{
	if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {
		isleftkeydown = 1;
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {
		isrightkeydown = 1;
	}
	if (isleftkeydown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)==0) {
			if (choice > 1) {
				choice -= 1;
			}
			isleftkeydown = 0;
		}
	}
	if (isrightkeydown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT) == 0) {
			if (choice < 3) {
				choice += 1;
			}
			isrightkeydown = 0;
		}
	}
	if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
		isEnterKeyDown = 1;
	}
	if (isEnterKeyDown == 1) {
		if (InputHandler::getInstance()->isKeyDown(DIK_RETURN) == 0) {
			isEnterKeyDown = 0;
			sceneState->switchBackToPreScene();
		}
	}
}

void MenuScene::update(DWORD dt)
{
	Scene::update(dt);
	SharedData* shareddate = SharedData::getInstance();
	charsets[0]->state = POWER_UP_HOMINGMISSLE;
	charsets[1]->state = POWER_UP_THUNDER;
	charsets[2]->state = POWER_UP_X3MISSLE;
	if (choice == 1) {
		charsets[0]->state = POWER_UP_HOMINGMISSLE_TICK;
	}
	if (choice == 2) {
		charsets[1]->state = POWER_UP_THUNDER_TICK;
	}
	if (choice == 3) {
		charsets[2]->state = POWER_UP_X3MISSLE_TICK;
	}

}

void MenuScene::onActivate()
{
}

void MenuScene::onDeactivated()
{
	SharedData::getInstance()->weapon = choice;
}

void MenuScene::render()
{
	LPANIMATION ani;
	for (int i = 0; i < 9; i++) {

		ani = AnimationManager::getInstance()->get(charsets[i]->state);
		ani->render(charsets[i]->x, charsets[i]->y);
	}


}
