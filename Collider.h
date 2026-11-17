#pragma once
#include "common.h"

class Collider
{
public:
	// 2つの円が重なっていたら true
	static bool CheckCircleHit(Vector2 posA, float radiusA, Vector2 posB, float radiusB);
};

