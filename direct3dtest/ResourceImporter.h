#pragma once
#include <wtypes.h>
#include <fstream>
#include "Debug.h"
#include <string>
#include <vector>
#include "SpriteManager.h"
#include "TextureManager.h"

class ResourceImporter
{
public:
	static void spriteImport(LPCSTR filename, SpriteManager* sprManager);
	static void mapDataImport(LPCSTR filename);
};

