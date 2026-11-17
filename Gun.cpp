#include <DxLib.h>
#include <cmath>
#include "Gun.h"
#include "common.h"
#include "PlayerInput.h"
#include "Camera.h"
#include "Neon.h"
#include "DebugDisplay.h"
#include "Collider.h"

void Gun::InitializeGun(int bulletCount)
{
	m_gun = { {0,0} ,96,96};
	m_bullet = { {0,0},{0,0} ,BULLET_RADIUS,BULLET_SPEED,false };

	m_magazine.assign(bulletCount, m_bullet);
}

void Gun::Shoot(Vector2 aimDirection, Vector2 shootPos)
{
	for (size_t i = 0; i < m_magazine.size(); i++) 
	{
		if (!m_magazine[i].isActive)
		{
			//マガジンの中のアクティブになってる弾に現在の位置を設定
			m_magazine[i].position.x = shootPos.x;
			m_magazine[i].position.y = shootPos.y;

			//発射方向計算
			float length =
				sqrtf(aimDirection.x * aimDirection.x + aimDirection.y * aimDirection.y);

			if (length <= 0.001f)
				return;

			m_magazine[i].isActive = true;

			//正規化
			aimDirection.x /= length;
			aimDirection.y /= length;

			m_magazine[i].direction.x = aimDirection.x;
			m_magazine[i].direction.y = aimDirection.y;

			break;
		}
	}
}

bool Gun::CheckHit(Vector2 targetPos, float targetRadius)
{
	for (size_t i = 0; i < m_magazine.size(); i++)
	{
		if (m_magazine[i].isActive)
		{
			if (Collider::CheckCircleHit(targetPos, targetRadius,
				m_magazine[i].position,
				m_magazine[i].radius))
			{
				m_magazine[i].isActive = false;
				return true;
			}
		}
	}

	return false;

}

void Gun::UpdateBullet(int stageWidth,int stageHeight) 
{
	for (size_t i = 0; i < m_magazine.size(); i++)
	{
		if (!m_magazine[i].isActive)
			continue;

		//弾移動
		m_magazine[i].position.x +=
			m_magazine[i].direction.x * m_magazine[i].bulletSpeed;

		m_magazine[i].position.y +=
			m_magazine[i].direction.y * m_magazine[i].bulletSpeed;

		//画面外判定
		if (m_magazine[i].position.x < 0 ||
			m_magazine[i].position.x > stageWidth ||
			m_magazine[i].position.y < 0 ||
			m_magazine[i].position.y > stageHeight)
		{
			m_magazine[i].isActive = false;
		}
	}
}

void Gun::DrawBullet(Camera camera, NeonColor color)
{
	for (size_t i = 0; i < m_magazine.size(); i++)
	{
		if (!m_magazine[i].isActive)
			continue;

		//弾描画(進行方向の後ろに尾を引く光の線)
		float headX = m_magazine[i].position.x - camera.m_x;
		float headY = m_magazine[i].position.y - camera.m_y;
		float tailX = headX - m_magazine[i].direction.x * BULLET_TAIL_LENGTH;
		float tailY = headY - m_magazine[i].direction.y * BULLET_TAIL_LENGTH;

		Neon::DrawGlowLine(tailX, tailY, headX, headY, color, 3.0f);
	}
}

void Gun::DrawSight() 
{
	Vector2 mouse = PlayerInput::GetMousePos();
	m_gun.position = mouse;

	float centerX = static_cast<float>(m_gun.position.x);
	float centerY = static_cast<float>(m_gun.position.y);
	float radius = m_gun.width / 4.0f;

	//サイト描画(光る円+上下左右の目盛り+中心の点)
	Neon::DrawGlowCircle(centerX, centerY, radius, Neon::MAGENTA, 2.0f);
	Neon::DrawGlowLine(centerX - radius - 8.0f, centerY, centerX - radius + 4.0f, centerY, Neon::MAGENTA, 2.0f);
	Neon::DrawGlowLine(centerX + radius - 4.0f, centerY, centerX + radius + 8.0f, centerY, Neon::MAGENTA, 2.0f);
	Neon::DrawGlowLine(centerX, centerY - radius - 8.0f, centerX, centerY - radius + 4.0f, Neon::MAGENTA, 2.0f);
	Neon::DrawGlowLine(centerX, centerY + radius - 4.0f, centerX, centerY + radius + 8.0f, Neon::MAGENTA, 2.0f);
	DrawCircleAA(centerX, centerY, 2.0f, 16, GetColor(255, 255, 255), TRUE);
}