#pragma once

class SceneStateMachine;

#include <vector>
#include "../gameObject/AllObject.h"
#include "../Camera.h"
#include "../SceneStateMachine.h"
#include"../hub/HeatlhBar.h"
#include"../hub/GunBar.h"
#include "../SoundManager.h"
#include "../ResourceImporter.h"



class ObjectGrid {
private:
	GameObject* obj;
	short gridX_start = 0;
	short gridY_start = 0;
	short gridX_end = 0;
	short gridY_end = 0;
public:
	ObjectGrid(GameObject* obj) {
		this->obj = obj;
		updateGridPos();
	}
	LPGAMEOBJECT getObj() { return obj; }
	void updateGridPos() {
		float t, l, b, r;
		obj->GetBoundingBox(t, l, b, r);
		gridX_start = short(l / (SCREEN_WIDTH / 2));
		gridY_start = short(t / (SCREEN_HEIGHT / 2));
		gridX_end = short(r / (SCREEN_WIDTH / 2));
		gridY_end = short(b / (SCREEN_HEIGHT / 2));
	}
	bool isNearby(const short &gridX_origin, const short &gridY_origin) {
		//FIXME:
		return !(gridX_end < gridX_origin - 1 || gridX_start > gridX_origin + 2 || gridY_end < gridY_origin - 1 || gridY_start > gridY_origin + 2);
	}
};

struct SectionGraphEdge {
	int dst;
	Portal* p;
};

class SectionGraph {
	std::vector < std::pair < SceneSection*, std::vector < SectionGraphEdge >* > > adjList;
public:
	void addSection(SceneSection* section) {
		adjList.push_back({ section, new std::vector<SectionGraphEdge> });
	}
	void addPortal(Portal* p) {
		adjList.at(p->getSectionStart()).second->push_back({p->getSectionEnd(), p});
	}
	SceneSection* getSection(int index) {
		return adjList.at(index).first;
	}
	std::vector<SectionGraphEdge>* getLinkedPortalList(int index) {
		return adjList.at(index).second;
	}
};

class Scene {
private:
	std::vector<LPGAMEOBJECT> coObjects;
protected:
	std::vector<ObjectGrid*> objectGridMap;
	int bgTexture_id = 0;
	int fgTexture_id = 0;
	Camera* cam;
	int activeSection = -1;
	SectionGraph sectionGraph;
	SceneStateMachine* sceneState;
	HeatlhBar* heatlhbar;
	GunBar* gunBar;
	int isEnterKeyDown = 0, isresetenemy=0;
	float spawnerX, spawnerY;
public:
	int fromintro = 1;
	Scene(SceneStateMachine* sceneState);
	void addObject(GameObject* obj);
	bool removeObject(GameObject* obj);
	void addSection(SceneSection* section);
	void addPortal(Portal* p);
	virtual void initScene() = 0;
	virtual void handlingInput() = 0;
	virtual void update(DWORD dt);
	virtual void render();
	virtual void renderHUD() {}
	Camera* getCamera() { return cam; }
	int getBgTexture_id() { return bgTexture_id; }
	int getFgTexture_id() { return fgTexture_id; }
	ScenePortal* PreScenePortal = NULL;

	virtual void onCreate() {}
	virtual void onDestroy() {}
	virtual void onActivate() {}
	virtual void onDeactivated() {}
	virtual int getCurrentSceneNumber(){ return 0; }
	bool resetSceneEnemy();
};