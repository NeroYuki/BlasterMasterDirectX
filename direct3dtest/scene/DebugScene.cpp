#include "DebugScene.h"

DebugScene::DebugScene(SceneStateMachine* sceneState) : Scene(sceneState)
{
	initScene();
	bgTexture_id = 6;
	fgTexture_id = 8;
	sectionSwitchTimer = new GameTimer(3000);
	switchSceneTimer = new GameTimer(500);
	bossSceneTimer = new GameTimer(3000);
	bossTimer = new GameTimer(1000);
	//spawnerX = 90;
	//spawnerY = 1420;
	//activeSection = 0;

}

void DebugScene::initScene()
{
	spawnerX = 625;
	spawnerY = 400;
	activeSection = 25;
	p_stack = new std::stack<Player*>();
	JasonTop* s = new JasonTop(spawnerX, spawnerY, 1);
	p_stack->push(s);
	this->addObject(s);
	s->setActiveSection(this->activeSection);
	cam->setFollow(p_stack->top());
	heatlhbar->setFollow(p_stack->top());
	gunBar->setFollow(p_stack->top());
	isBossFight = 0;
}

void DebugScene::handlingInput()
{
	int control_state = 0;
	if (p_stack->top()->getInvincible() != 1) {

		if (InputHandler::getInstance()->isKeyDown(DIK_DOWN)) {
			control_state += DOWN;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_UP)) {
			control_state += UP;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {
			control_state += LEFT;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {
			control_state += RIGHT;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_Z)) {
			control_state += PRIMARY;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_X)) {
			control_state += SECONDARY;
		}
		if (InputHandler::getInstance()->isKeyDown(DIK_LSHIFT)) {
			//spawn a small jason and switch 
		}
		p_stack->top()->setControlState(control_state);
		if (InputHandler::getInstance()->isKeyDown(DIK_RETURN)) {
			isEnterKeyDown = 1;
		}
		if (isEnterKeyDown == 1) {
			if (InputHandler::getInstance()->isKeyDown(DIK_RETURN) == 0) {
				isEnterKeyDown = 0;
				int sceneid = sceneState->getSceneByLabel("Menu");
				sceneState->switchToScene(sceneid);
			}
		}
	}
}

void DebugScene::update(DWORD dt) {
	Scene::update(dt);
	heatlhbar->update(cam);
	gunBar->update(cam);
	BulletManager* r = BulletManager::getinstance();
	if (r->getBullet()->size() != 0) {
		for (int i = 0; i < r->getBullet()->size(); i++)
		{
			this->addObject(r->getBullet()->at(i));
		}
		r->getBullet()->clear();
	}
	if (r->getDeleteBullet()->size() != 0) {
		for (int i = 0; i < r->getDeleteBullet()->size(); i++)
		{
			this->removeObject(r->getDeleteBullet()->at(i));
		}
		r->getDeleteBullet()->clear();
	}
	CollectableManager* c = CollectableManager::getinstance();
	if (c->getCollectable()->size() != 0) {
		for (int i = 0; i < c->getCollectable()->size(); i++)
		{
			this->addObject(c->getCollectable()->at(i));
		}
		c->getCollectable()->clear();
	}
	//attempt section switching logic
	if (p_stack->top()->getActiveSection() != activeSection) {
		if (!sectionSwitchTimer->isStarted())
			sectionSwitchTimer->start();
	}

	if (p_stack->top()->getIsChangeScene() == 1) {
		if (!switchSceneTimer->isStarted())
			switchSceneTimer->start();
		p_stack->top()->setIsChangeScence(0);
	}

	short timerState = sectionSwitchTimer->update(dt);
	short timerState2 = switchSceneTimer->update(dt);
	short timerState3 = bossSceneTimer->update(dt);
	short timerState4 = bossTimer->update(dt);
	if (this->activeSection == 28 && isBossFight == 0) {
		isBossFight = 1;
		this->bgTexture_id = 30;
		this->fgTexture_id = 30;
		bossSceneTimer->restart();
	}
	if (timerState3 == TIMER_STARTED) {
		if (SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_BG_AREA2) == true) {
			SoundManager::getInstance()->Stop(eSoundId::SOUND_BG_AREA2);
		}
		SoundManager::getInstance()->Play(eSoundId::SOUND_BOSS_WARNING);
	}
	if (timerState3 == TIMER_ENDED) {
		SoundManager::getInstance()->PlayLoop(eSoundId::BOSS_BG);
		if (SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_BOSS_WARNING) == true) {
			SoundManager::getInstance()->Stop(eSoundId::SOUND_BOSS_WARNING);
		}
		boss = new Boss(spawnerX - 30, spawnerY - 150, 20);
		this->addObject(boss);

		bossjoints1[0] = new  BossJoint(spawnerX - 30, spawnerY, 30, 0, 15);
		for (int i = 1; i < 5; i++) {
			bossjoints1[i] = new BossJoint(bossjoints1[i - 1], 30, 1);
		}
		bossjoints1[4]->setState(1);
		for (int i = 0; i < 5; i++) {
			this->addObject(bossjoints1[i]);
		}

		bossjoints2[0] = new  BossJoint(spawnerX - 30, spawnerY, 30, 0, 15);
		for (int i = 1; i < 5; i++) {
			bossjoints2[i] = new BossJoint(bossjoints2[i - 1], 30, 1);
		}
		bossjoints2[4]->setState(2);
		for (int i = 0; i < 5; i++) {
			this->addObject(bossjoints2[i]);
		}

		this->fgTexture_id = 0;
		this->bgTexture_id = 0;
		tempdx = spawnerX - 30;
		tempdy = spawnerY;
		tempdx2 = spawnerX + 30;
		tempdy2 = spawnerY;
	}
	if (boss != NULL) {
		if (boss->getisDie() == 1) {
			SoundManager::getInstance()->Stop(eSoundId::BOSS_BG);
			this->isBossFight = 0;
			int sceneid = sceneState->getSceneByLabel("Ending");
			//Scene* returnScene = sceneState->getSceneById(sceneid);
			//returnScene->PreScenePortal = portal;

			sceneState->switchToScene(sceneid);
		}
		if (boss->getisDie() != 2) {
			jointUpdate();
		}
	}


	if (timerState == TIMER_STARTED) {
		p_stack->top()->setIgnoreCollision(true);
		//find the corresponded portal
		std::vector<SectionGraphEdge>* portalList = sectionGraph.getLinkedPortalList(activeSection);
		for (int i = 0; i < portalList->size(); i++) {
			if (portalList->at(i).dst == p_stack->top()->getActiveSection()) {
				Portal* checking_portal = portalList->at(i).p;

				float lx = checking_portal->getLx();
				float ly = checking_portal->getLy();
				int forceControlState = 0;

				if (lx > 0) forceControlState += RIGHT;
				if (lx < 0) forceControlState += LEFT;
				if (ly > 0) forceControlState += DOWN;
				if (ly < 0) forceControlState += UP;
				p_stack->top()->setForceControlState(forceControlState);

				long interval = max(abs(lx) / PLAYER_WALKING_SPEED, abs(ly) / PLAYER_WALKING_SPEED) + 500;
				sectionSwitchTimer->setInterval(interval);

				float lcx = 0, lcy = 0;
				if (lx > 0) { lcx = cam->getW(); }
				if (lx < 0) { lcx = -cam->getW(); }
				if (ly > 0) { lcy = cam->getH() + 32; }
				if (ly < 0) { lcy = -(cam->getH() + 32); }

				cam->setForceVeloc(lcx / interval, lcy / interval);
				cam->updateWithForceVeloc(dt);
			}
		}
	}

	else if (timerState == TIMER_ACTIVE) {
		cam->updateWithForceVeloc(dt);
	}
	else if (timerState == TIMER_ENDED) {
		p_stack->top()->setForceControlState(IDLE);
		p_stack->top()->setIgnoreCollision(false);
		activeSection = p_stack->top()->getActiveSection();
		cam->setForceVeloc(0, 0);
		p_stack->top()->getPos(spawnerX, spawnerY);
	}
	if (timerState2 == TIMER_STARTED) {
		ScenePortal* portal = p_stack->top()->getScenePortal();
		if (portal != NULL) {
			int sceneid = sceneState->getSceneByLabel("Overworld");

			Scene* returnScene = sceneState->getSceneById(sceneid);
			returnScene->PreScenePortal = portal;

			sceneState->switchToScene(sceneid);
		}
	}
	if (p_stack->top()->getisDie() == 2) {
		if (dynamic_cast<Jason*>(p_stack->top())) {
			Jason* jason_p = dynamic_cast<Jason*>(p_stack->top());
			jason_p->unfollow();
			p_stack->pop();
			this->removeObject(jason_p);
			p_stack->top()->resetPlayer(spawnerX, spawnerY);
			cam->setFollow(p_stack->top());
			heatlhbar->setFollow(p_stack->top());
		}
		else {
			p_stack->top()->resetPlayer(spawnerX, spawnerY);
			cam->setFollow(p_stack->top());
			heatlhbar->setFollow(p_stack->top());
		}
		this->isBossFight = 0;
		int sceneid = sceneState->getSceneByLabel("DeadScene");
		isresetenemy = 1;
		sceneState->switchToScene(sceneid);
	}
}

void DebugScene::onActivate() {

	if (PreScenePortal != NULL) {
		p_stack->top()->setForceControlState(IDLE);
		p_stack->top()->setIgnoreCollision(false);
		int section = PreScenePortal->getSectionEnd();
		this->spawnerX= PreScenePortal->getLx();
		this->spawnerY= PreScenePortal->getLy();
		p_stack->top()->resetPlayer(spawnerX, spawnerY);
		p_stack->top()->setActiveSection(section);
		activeSection = p_stack->top()->getActiveSection();
		cam->update(this->sectionGraph.getSection(section));
		cam->setForceVeloc(0, 0);
		for (std::vector<ObjectGrid*>::iterator it = objectGridMap.begin(); it != objectGridMap.end(); ++it)
		{
			(*it)->updateGridPos();
		}
		this->PreScenePortal = NULL;
		heatlhbar->setFollow(p_stack->top());
		gunBar->setFollow(p_stack->top());
	}
	if (boss != NULL) {
		this->boss->setisdie();
		for (int i = 0; i < 5; i++) {
			bossjoints1[i]->setisdie();
			bossjoints2[i]->setisdie();
		}
	}
	if (SoundManager::getInstance()->IsPlaying(eSoundId::SOUND_BG_AREA2) == false) {
		SoundManager::getInstance()->PlayLoop(eSoundId::SOUND_BG_AREA2);
	}

}
void DebugScene::onDeAtivate() {


	if (isresetenemy == 1)
		this->resetSceneEnemy();
	isresetenemy = -1;
}
void DebugScene::renderHUD()
{
	heatlhbar->render();
	gunBar->render();
}


DebugScene::~DebugScene() {
	//deallocate player control stack and object pool
}
void DebugScene::jointUpdate() {
	if (bossTimer->peekState() == TIMER_INACTIVE) {
		randomx = SharedData::getInstance()->getRandomNumber();
		randomy = SharedData::getInstance()->getRandomNumber();
		//	int randomy = SharedData::getInstance()->getRandomNumber();

		bossTimer->restart();
	}
	tempdy += randomx % 7 - 3;
	tempdx += randomy % 7 - 3;
	tempdx2 += randomx % 7 - 3;
	tempdy2 += randomy % 7 - 3;

	if (tempdy < 0) tempdy = 0;
	if (tempdy > 256) tempdy = 256;
	if (tempdx < 760) tempdx = 760;
	if (tempdx > 860) tempdx = 860;
	if (tempdy2 < 0) tempdy2 = 0;
	if (tempdy2> 256) tempdy2 = 256;
	if (tempdx2 < 924) tempdx2 = 924;
	if (tempdx2 > 1024) tempdx2 = 1024;

//	if (tempdx < 0) tempdx = spawnerX;
//	if (tempdy > spawnerY + 150) tempdy = spawnerY - 150;
//	else  if (tempdy < spawnerY - 150) tempdy = spawnerY + 150;

	if (bossjoints1[4] != NULL) {
		bossjoints1[4]->follow(tempdx, tempdy);
		bossjoints1[4]->update();
		for (int i = 3; i >= 0; i--) {
			bossjoints1[i]->follow(bossjoints1[i + 1]);
			bossjoints1[i]->update();
		}
		float bossx, bossy;
		boss->getLeftHand(bossx, bossy);
		bossjoints1[0]->setPos(bossx, bossy);

		bossjoints1[0]->calculateB();
		for (int i = 1; i < 5; i++) {
			bossjoints1[i]->setPos(bossjoints1[i - 1]->x2, bossjoints1[i - 1]->y2);
			bossjoints1[i]->calculateB();
		}
		//		bossTimer->restart();
	}
	if (bossjoints2[4] != NULL) {
		bossjoints2[4]->follow(tempdx2 , tempdy2);
		bossjoints2[4]->update();
		for (int i = 3; i >= 0; i--) {
			bossjoints2[i]->follow(bossjoints2[i + 1]);
			bossjoints2[i]->update();
		}
		float bossx = spawnerX, bossy = spawnerY;
		boss->getRightHand(bossx, bossy);
		bossjoints2[0]->setPos(bossx, bossy);

		bossjoints2[0]->calculateB();
		for (int i = 1; i < 5; i++) {
			bossjoints2[i]->setPos(bossjoints2[i - 1]->x2, bossjoints2[i - 1]->y2);
			bossjoints2[i]->calculateB();
		}
		//		bossTimer->restart();
	}
	//bossTimer->restart();

	//	}
}


void abandoned() {
	//int res_jsTop = 0;
	//int res_js = 0;
	//int res_sophia = 0;
	//if (InputHandler::getInstance()->isKeyDown(DIK_W)) {
	//	jsTop->changeState(TOP_JASON_WALK_UP);
	//	res_jsTop += UP;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_A)) {
	//	jsTop->changeState(TOP_JASON_WALK_LEFT);
	//	res_jsTop += LEFT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_S)) {
	//	jsTop->changeState(TOP_JASON_WALK_DOWN);
	//	res_jsTop += DOWN;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_D)) {
	//	jsTop->changeState(TOP_JASON_WALK_RIGHT);
	//	res_jsTop += RIGHT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_RIGHT)) {
	//	if (js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_CRAW_RIGHT);
	//	}
	//	else //if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT || js->getState() == JASON_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_WALK_RIGHT);
	//	}
	//	if (sophia->getState() == SOPHIA_IDLE_LEFT || sophia->getState() == SOPHIA_MOVE_LEFT)
	//	{
	//		sophia->changeState(SOPHIA_TURN_RIGHT);
	//		res_sophia -= RIGHT;
	//	}
	//	else
	//	{
	//		sophia->changeState(SOPHIA_MOVE_RIGHT);
	//	}
	//	res_js += RIGHT;
	//	res_sophia += RIGHT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_LEFT)) {
	//	if (js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_CRAW_LEFT);
	//	}
	//	else //if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT || js->getState() == JASON_IDLE_RIGHT)
	//	{
	//		js->changeState(JASON_WALK_LEFT);
	//	}
	//	if (sophia->getState() == SOPHIA_IDLE_RIGHT || sophia->getState() == SOPHIA_MOVE_RIGHT)
	//	{
	//		sophia->changeState(SOPHIA_TURN_LEFT);
	//		res_sophia -= LEFT;
	//	}
	//	else
	//	{
	//		sophia->changeState(SOPHIA_MOVE_LEFT);
	//	}
	//	res_sophia += LEFT;
	//	res_js += LEFT;
	//}
	//if (InputHandler::getInstance()->isKeyDown(DIK_DOWN)) {
	//	js->changeState(COMMON_JASON_CRAW_IDLE);
	//	js->setCrawState(true);
	//}

	//if (InputHandler::getInstance()->isKeyDown(DIK_UP)) {
	//	if (js->getState() == js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//		js->changeState(COMMON_JASON_IDLE);
	//	js->setCrawState(false);
	//}

	//if (InputHandler::getInstance()->isKeyDown(DIK_X)) {
	//	if (!js->getCrawState())
	//	{
	//		if (js->getState() == JASON_IDLE_LEFT || js->getState() == JASON_WALK_LEFT)
	//		{
	//			js->changeState(JASON_JUMP_LEFT);
	//		}
	//		else if (js->getState() == JASON_IDLE_RIGHT || js->getState() == JASON_WALK_RIGHT)
	//		{
	//			js->changeState(JASON_JUMP_RIGHT);
	//		}
	//		res_js += JUMP;
	//	}
	//	if (sophia->getState() == SOPHIA_MOVE_RIGHT || sophia->getState() == SOPHIA_IDLE_RIGHT) {
	//		sophia->changeState(SOPHIA_JUMP_RIGHT);
	//	}
	//	else if (sophia->getState() == SOPHIA_MOVE_LEFT || sophia->getState() == SOPHIA_MOVE_LEFT) {
	//		sophia->changeState(SOPHIA_JUMP_LEFT);
	//	}
	//	res_sophia += JUMP;
	//}
	//jsTop->setControlState(res_jsTop);
	//js->setControlState(res_js);
	//sophia->setControlState(res_sophia);
	//if (res_js == 0) {
	//	if (js->getState() == JASON_CRAW_LEFT || js->getState() == JASON_CRAW_RIGHT || js->getState() == JASON_CRAW_IDLE_LEFT || js->getState() == JASON_CRAW_IDLE_RIGHT)
	//		js->changeState(COMMON_JASON_CRAW_IDLE);
	//	else
	//		js->changeState(COMMON_JASON_IDLE);
	//}
	//if (res_jsTop == 0) {
	//	jsTop->changeState(COMMON_PLAYER_IDLE);
	//}
	//if (res_sophia == 0) {
	//	sophia->changeState(COMMON_SOPHIA_IDLE);
	//}
}