#pragma once
#include "common.h"

class Collider
{
public:
	// 2つの円が重なっていたら true
	static bool CheckCircleHit(FloatVector2 posA, float radiusA, FloatVector2 posB, float radiusB);
};

