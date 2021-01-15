#pragma once
#include <wtypes.h>
#include <fstream>
#include "Debug.h"
#include <string>
#include <vector>
#include "SpriteManager.h"
#include "TextureManager.h"
#include "AnimationManger.h"
#include "scene/Scene.h"

class ResourceImporter
{
public:
	static void spriteImport(LPCSTR filename, SpriteManager* sprManager, AnimationManager* aniManager);
	static void mapDataImport(LPCSTR filename, Scene* applyingScene);
	static void mapObjImport(LPCSTR filename, Scene* applyingScene);
	static void enemyImport(LPCSTR filename, Scene* applyingScene);
	static void tilesetImporter(LPCSTR filename);
};

