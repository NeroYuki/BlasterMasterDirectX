#pragma once
#include <algorithm>

class CollisionHelper {
public:
	static void sweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny);
};

