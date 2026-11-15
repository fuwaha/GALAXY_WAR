#include "Enemy.h"
#include "common.h"
#include "Neon.h"
#include "DebugDisplay.h"
#include <DxLib.h>
#include <cmath>

Enemy::EnemyState Enemy::GetEnemyState() const
{
	return m_enemyState;
}

void Enemy::SetEnemyState(EnemyState state) 
{
	m_enemyState = state;
}

FloatVector2 Enemy::GetPosition() const 
{
	return m_exactPos;
}

float Enemy::GetRadius() const 
{
	return DRAW_RADIUS;
}

void Enemy::InitializeEnemy(Vector2 spawnPos) 
{
	m_isActive = false;

	m_enemyPosX = spawnPos.x;
	m_enemyPosY = spawnPos.y;
	m_enemyW = static_cast<int>(DRAW_RADIUS * 2);
	m_enemyH = static_cast<int>(DRAW_RADIUS * 2);

	m_enemyObj = { { m_enemyPosX,m_enemyPosY },m_enemyW,m_enemyH};

	m_exactPos = { static_cast<float>(m_enemyPosX), static_cast<float>(m_enemyPosY) };

	m_enemyState = EnemyState::Alive;

	m_flashTimer = 0;
	m_shootTimer = 0;

	m_hitPoint.Initialize(MAX_HP);
	m_gun.InitializeGun(BULLET_COUNT);
}

void Enemy::DrawEnemy(Camera camera) 
{
	if (DebugDisplay::IsVisible())
	{
		DrawFormatString(20, 180, GetColor(255, 255, 0), L"EnemyHP:%d", m_hitPoint.GetHp());
	}

	m_gun.DrawBullet(camera, Neon::RED);

	// 死んでいたら描かない
	if (m_enemyState == EnemyState::Dead)
		return;

	// ワールド座標から画面座標に変換
	float screenX = static_cast<float>(m_enemyObj.position.x - camera.m_x);
	float screenY = static_cast<float>(m_enemyObj.position.y - camera.m_y);

	float eyeX = screenX + cosf(m_angle) * EYE_DISTANCE;
	float eyeY = screenY + sinf(m_angle) * EYE_DISTANCE;

	switch (m_enemyState)
	{
	case EnemyState::Alive:
	{
		// 体(オレンジの丸)
		Neon::DrawGlowCircle(screenX, screenY, DRAW_RADIUS, Neon::ORANGE, BODY_THICKNESS);
		// 目(赤い点、プレイヤーの方向にずらして描く)
		Neon::DrawGlowCircle(eyeX, eyeY, EYE_RADIUS, Neon::RED, EYE_THICKNESS);
	}
	break;
	case EnemyState::Damage:
	{
		Neon::DrawGlowCircle(screenX, screenY, DRAW_RADIUS, Neon::WHITE, BODY_THICKNESS);

		if (m_flashTimer / 3 % 2 == 0)
			Neon::DrawGlowCircle(eyeX, eyeY, EYE_RADIUS, Neon::RED, EYE_THICKNESS);
	}
	break;
	}

}

void Enemy::UpdateEnemy(int stageWidth, int stageHeight, Vector2 playerPos) 
{
	m_gun.UpdateBullet(stageWidth, stageHeight);

	if (m_enemyState == EnemyState::Dead) 
	{
		m_isActive = false;
		return;
	}

	// プレイヤーの方向の角度を計算(目の向きに使う)
	float dx = static_cast<float>(playerPos.x - m_enemyObj.position.x);
	float dy = static_cast<float>(playerPos.y - m_enemyObj.position.y);
	m_angle = atan2f(dy, dx);

	float length = sqrtf(dx * dx + dy * dy);

	if (length > 0.001f)	// 重なってたら0で割っちゃうので何もしない
	{
		m_exactPos.x += dx / length * MOVE_SPEED;
		m_exactPos.y += dy / length * MOVE_SPEED;

		m_enemyObj.position = { static_cast<int>(m_exactPos.x),static_cast<int>(m_exactPos.y) };
	}

	switch (m_enemyState)
	{
	case EnemyState::Alive:
	{
		if (m_shootTimer <= 0) 
		{
			m_gun.Shoot({ dx,dy }, m_enemyObj.position);
			m_shootTimer = SHOOT_TIME;
		}

		m_shootTimer -= 1;
	}
	break;
	case EnemyState::Damage:
	{
		m_flashTimer -= 1;

		if (m_flashTimer <= 0)
			m_enemyState = EnemyState::Alive;
	}
	break;
	}
}

bool Enemy::CheckBulletHit(FloatVector2 targetPos, float targetRadius)
{
	return m_gun.CheckHit(targetPos, targetRadius);
}

void Enemy::TakeDamage(int amount)
{
	m_hitPoint.Damage(amount);

	if (m_hitPoint.IsDead())
	{
		m_enemyState = EnemyState::Dead;
	}
	else
	{
		m_enemyState = EnemyState::Damage;
		m_flashTimer = FLASH_TIME;
	}
}

bool Enemy::IsActive() const
{
	return m_isActive;
}

void Enemy::Activate() 
{
	m_isActive = true;
}