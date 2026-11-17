#pragma once
#include <cmath>

struct Vector2
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
	Vector2 position;
	Vector2 direction;

	float radius;

	float bulletSpeed;
	bool isActive;
};

inline Vector2 Direction(Vector2 from, Vector2 to)
{
	Vector2 dir = { to.x - from.x, to.y - from.y };
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

inline float Distance(Vector2 from, Vector2 to)
{
	Vector2 dir = { to.x - from.x, to.y - from.y };
	return sqrtf(dir.x * dir.x + dir.y * dir.y);
}

inline float Angle(Vector2 from, Vector2 to)
{
	Vector2 dir = { to.x - from.x, to.y - from.y };
	return atan2f(dir.y, dir.x);
}