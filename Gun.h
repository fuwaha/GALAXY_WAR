#pragma once
#include "common.h"
#include "Camera.h"
#include <vector>
#include "Neon.h"

class Gun
{
public:
	void InitializeGun(int bulletCount);
	void Shoot(Vector2 aimDirection, Vector2 vector2);
	bool CheckHit(Vector2 targetPos, float targetRadius);
	void DrawBullet(Camera camera ,NeonColor color);
	void UpdateBullet(int stageWidth, int stageHeight);
	void DrawSight();

private:
	static constexpr float BULLET_TAIL_LENGTH = 18.0f;	// 弾の光の尾の長さ

	static constexpr float BULLET_RADIUS = 4.0f;

	static constexpr float BULLET_SPEED = 16;

	GameObject m_gun;
	Bullet m_bullet;
	std::vector<Bullet> m_magazine;
};