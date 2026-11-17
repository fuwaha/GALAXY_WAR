#include "Collider.h"

bool Collider::CheckCircleHit(Vector2 posA, float radiusA, Vector2 posB, float radiusB)
{
	float dx = posA.x - posB.x;
	float dy = posA.y - posB.y;

	float distanceSq = dx * dx + dy * dy;

	float radiusSum = radiusA + radiusB;

	return distanceSq <= (radiusSum * radiusSum);
}