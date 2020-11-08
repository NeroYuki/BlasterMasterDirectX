#pragma once
#include <vector>
#include "../gameObject/AllObject.h"
#include "../Camera.h"

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

class Scene {
private:
	std::vector<ObjectGrid*> objectGridMap;
	std::vector<LPGAMEOBJECT> coObjects;
protected:
	int bgTexture_id = 0;
	int fgTexture_id = 0;
	Camera* cam;
public:
	Scene();
	void addObject(GameObject* obj);
	virtual void initScene() = 0;
	virtual void handlingInput() = 0;
	virtual void update(DWORD dt);
	void render();
	Camera* getCamera() { return cam; }

	int getBgTexture_id() { return bgTexture_id; }
	int getFgTexture_id() { return fgTexture_id; }

	virtual void onCreate() {}
	virtual void onDestroy() {}
	virtual void onActivate() {}
	virtual void onDeactivated() {}
};