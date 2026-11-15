#include "Collider.h"

bool Collider::CheckCircleHit(FloatVector2 posA, float radiusA, FloatVector2 posB, float radiusB)
{
	float dx = posA.x - posB.x;
	float dy = posA.y - posB.y;

	float distanceSq = dx * dx + dy * dy;

	float radiusSum = radiusA + radiusB;

	return distanceSq <= (radiusSum * radiusSum);
}