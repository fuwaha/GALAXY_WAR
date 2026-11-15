#pragma once

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