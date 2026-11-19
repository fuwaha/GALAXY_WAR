#include "Enemy.h"
#include "common.h"
#include "Neon.h"
#include "DebugDisplay.h"
#include "Score.h"
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

Vector2 Enemy::GetPosition() const 
{
	return m_enemyObj.position;
}

float Enemy::GetRadius() const 
{
	return m_param.drawRadius;
}

void Enemy::InitializeEnemy(Vector2 spawnPos,EnemyType enemyType) 
{
	m_enemyType = enemyType;
	m_param = ENEMY_LIST[static_cast<int>(enemyType)];

	m_enemyW = static_cast<int>(m_param.drawRadius * 2);
	m_enemyH = static_cast<int>(m_param.drawRadius * 2);

	m_enemyObj = { spawnPos,m_enemyW,m_enemyH };

	m_enemyState = EnemyState::Alive;

	m_flashTimer = 0;
	m_shootTimer = 0;

	m_hitPoint.Initialize(m_param.maxHp);
	m_gun.InitializeGun(m_param.bulletCount);
}

void Enemy::DrawEnemy(Camera camera) 
{
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
	m_angle = GetAngle(m_enemyObj.position, playerPos);
	Vector2 dir = GetDirection(m_enemyObj.position, playerPos);

	m_enemyObj.position =
	{
		m_enemyObj.position.x + dir.x * m_param.moveSpeed,
		m_enemyObj.position.y + dir.y * m_param.moveSpeed
	};

	switch (m_enemyState)
	{
	case EnemyState::Alive:
	{
		if (m_shootTimer <= 0)
		{
			m_gun.Shoot(dir, m_enemyObj.position);
			m_shootTimer = static_cast<int>(m_param.shootInterval) * GameSettings::FPS;
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

bool Enemy::CheckBulletHit(Vector2 targetPos, float targetRadius)
{
	return m_gun.CheckHit(targetPos, targetRadius);
}

void Enemy::TakeDamage(int amount)
{
	m_hitPoint.Damage(amount);

	if (m_hitPoint.IsDead())
	{
		m_enemyState = EnemyState::Dead;
		Score::AddScore(m_param.destroyScore);
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