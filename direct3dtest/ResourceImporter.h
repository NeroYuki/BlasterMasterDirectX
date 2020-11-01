#pragma once
#include <wtypes.h>
#include <fstream>
#include "Debug.h"
#include <string>
#include <vector>
#include "SpriteManager.h"
#include "TextureManager.h"
#include "AnimationManger.h"

class ResourceImporter
{
public:
	static void spriteImport(LPCSTR filename, SpriteManager* sprManager, AnimationManager* aniManager);
	static void mapDataImport(LPCSTR filename);
	static void mapObjImport(LPCSTR filename);
	static void tilesetImporter(LPCSTR filename);
};

