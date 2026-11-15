#include <DxLib.h>
#include <algorithm>
#include "InGameScene.h"
#include "PlayerInput.h"
#include "Collider.h"
#include "HpBar.h"

void InGameScene::Initialize()
{
	m_player.InitializePlayer();
	m_stage.InitializeStage();
	m_camera.InitializeCamera();

	m_enemyPool.resize(MAX_ENEMY_COUNT);
	m_spawnTimer = 0;
}

void InGameScene::Update()
{
	for (size_t i = 0; i < m_enemyPool.size(); i++)
	{
		//攻撃判定(敵がアクティブじゃないなら無視)
		if (!m_enemyPool[i].IsActive()) continue;

		//プレイヤーの攻撃判定
		if (m_enemyPool[i].GetEnemyState() != Enemy::EnemyState::Dead
			&& m_player.CheckBulletHit(m_enemyPool[i].GetPosition(),
				m_enemyPool[i].GetRadius()))
		{
			m_enemyPool[i].TakeDamage(m_player.ATTACK);
		}

		//敵の攻撃判定
		if (m_player.GetPlayerState() != Player::PlayerState::Dead)
		{
			//弾
			if (m_enemyPool[i].CheckBulletHit(m_player.GetPosition(), m_player.GetRadius()))
				m_player.TakeDamage(m_enemyPool[i].ATTACK);

			//体当たり
			if (Collider::CheckCircleHit
			(m_player.GetPosition(), m_player.GetRadius(),
				m_enemyPool[i].GetPosition(), m_enemyPool[i].GetRadius()))
				m_player.TakeDamage(m_enemyPool[i].ATTACK / 2);
		}
	}

	// プレイヤーの移動
	m_player.UpdatePlayer(m_stage.m_width,m_stage.m_height,m_camera);

	//敵のスポーン
	if (m_spawnTimer <= 0)
	{
		for (size_t i = 0; i < m_enemyPool.size(); i++)
		{
			if (m_enemyPool[i].IsActive()) continue;

			float spawnAngle = GetRand(359) * DX_PI_F / 180.0f;	// 0〜359度をラジアンに
			int spawnPosX = m_player.m_playerObj.position.x + static_cast<int>(cosf(spawnAngle) * SPAWN_DISTANCE);
			int spawnPosY = m_player.m_playerObj.position.y + static_cast<int>(sinf(spawnAngle) * SPAWN_DISTANCE);

			m_enemyPool[i].InitializeEnemy({ spawnPosX,spawnPosY });
			m_enemyPool[i].Activate();
			break;
		}

		m_spawnTimer = SPAWN_TIME;
	}
	m_spawnTimer -= 1;

	//敵の移動
	for (size_t i = 0; i < m_enemyPool.size(); i++) 
	{
		if (m_enemyPool[i].IsActive())
			m_enemyPool[i].UpdateEnemy(m_stage.m_width, m_stage.m_height, m_player.m_playerObj.position);
	}
}

void InGameScene::Draw()
{
	// ステージの描画
	m_stage.DrawStage(m_camera);
	// プレイヤーの描画
	m_camera.FollowCamera(m_player.m_playerObj.position, m_stage.m_width, m_stage.m_height);
	m_player.DrawPlayer(m_camera);

	for (size_t i = 0; i < m_enemyPool.size(); i++) 
	{
		if (m_enemyPool[i].IsActive())
			m_enemyPool[i].DrawEnemy(m_camera);
	}

	HpBar::Draw(m_player.GetHitPoint().GetHp(), m_player.GetHitPoint().GetMaxHp());
}

bool InGameScene::IsInGameEnd() const 
{
	return m_player.GetPlayerState() == Player::PlayerState::Dead;
}