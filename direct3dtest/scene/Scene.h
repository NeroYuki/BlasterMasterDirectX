#pragma once
#include <vector>
#include "../gameObject/AllObject.h"
#include "../Camera.h"


class Scene {
private:
	std::vector<GameObject*> objectPool;
protected:
	int bgTexture_id = 0;
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

	virtual void onCreate() {}
	virtual void onDestroy() {}
	virtual void onActivate() {}
	virtual void onDeactivated() {}
};