#pragma once
#include <cmath>

struct Vector2
{
	int x;
	int y;
};

struct FloatVector2 
{
	float x;
	float y;
};

struct GameObject
{
	Vector2 position;
	int width;
	int height;
	bool IsActive;
};

struct Bullet
{
	FloatVector2 position;
	FloatVector2 direction;

	float radius;

	float bulletSpeed;
	bool isActive;
};

inline FloatVector2 Direction(FloatVector2 from, FloatVector2 to)
{
	FloatVector2 dir = { to.x - from.x, to.y - from.y };
	float dis = sqrtf(dir.x * dir.x + dir.y * dir.y);

	if (dis > 0.001f)
	{
		//正規化
		dir.x /= dis;
		dir.y /= dis;

		return dir;
	}

	return { 0,0 };
}

inline float Distance(FloatVector2 from, FloatVector2 to)
{
	FloatVector2 dir = { to.x - from.x, to.y - from.y };
	return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

inline float Angle(FloatVector2 from, FloatVector2 to)
{
	FloatVector2 dir = { to.x - from.x, to.y - from.y };
	return atan2f(dir.y, dir.x);
}