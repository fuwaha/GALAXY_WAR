#pragma once

#include "common.h"
#include "Camera.h"
#include "HitPoint.h"
#include "GameSettings.h"
#include "Gun.h"

class Enemy
{
public:
	enum class EnemyState
	{
		Alive,
		Dead,
		Damage
	};

	EnemyState GetEnemyState() const;
	void SetEnemyState(EnemyState state);

	Vector2 GetPosition() const;
	float GetRadius() const;

	void InitializeEnemy(Vector2 spawnPos);

	void DrawEnemy(Camera camera);
	void UpdateEnemy(int stageWidth, int stageHeight, Vector2 playerPos);

	bool CheckBulletHit(Vector2 targetPos, float targetRadius);

	void TakeDamage(int amount);

	bool IsActive() const;
	void Activate();

	static const int ATTACK = 10;

private:
	GameObject m_enemyObj;

	bool m_isActive = false;

	//位置
	float m_enemyPosX;
	float m_enemyPosY;

	//大きさ(あたり判定用、表示に使う大きさはDRAW_RADIUS)
	int m_enemyW;
	int m_enemyH;

	//この敵を倒した時にもらえるスコア
	static const int DESTROY_SCORE = 100;

	Vector2 m_exactPos = { 0.0f,0.0f };

	static constexpr float MOVE_SPEED = 2.0f;

	//HPのインスタンスと最大値の設定
	HitPoint m_hitPoint;
	static const int MAX_HP = 2;

	//弾を発射する銃
	Gun m_gun;
	static const int BULLET_COUNT = 3; //弾数
	int m_shootTimer = 0;              //インターバル用のタイマー
	static const int SHOOT_TIME = 60;  //弾発射のインターバル

	//攻撃を受けた時の点滅(プレイヤーには無敵時間があるけど、敵には無し)
	int m_flashTimer = 0;
	static const int FLASH_TIME = 20;

	EnemyState m_enemyState = EnemyState::Alive;

	float m_angle = 0.0f;	// プレイヤーの方を向いている角度(ラジアン)

	static constexpr float DRAW_RADIUS = 32.0f;		// 体の円の半径
	static constexpr float BODY_THICKNESS = 3.0f;	// 体の線の太さ
	static constexpr float EYE_DISTANCE = 16.0f;	// 中心から目までの距離
	static constexpr float EYE_RADIUS = 4.0f;		// 目の半径
	static constexpr float EYE_THICKNESS = 4.0f;	// 目の線の太さ(半径と同じくらいにすると塗りつぶした点に見える)
};